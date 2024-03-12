import os
import sys

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session.get("user_id")
    #dictionary to store stock info
    stockList = db.execute("SELECT symbol, SUM(quantity) FROM transactions WHERE user_id = ? GROUP BY symbol", user)
    print(stockList)

    # look up current price and add it to each row
    for dict in stockList:
        stockInfo = lookup(dict["symbol"])
        currentPrice = stockInfo["price"]
        dict["price"] = currentPrice

    # find total value of each stock holding
    totalValueSum = 0
    for dict in stockList:
        totalValue = dict["SUM(quantity)"] * dict["price"]
        dict["total_value"] = totalValue
        totalValueSum += totalValue
        print(stockList)

    # get user's current cash balance and grand total holdings
    userBalance = db.execute("SELECT cash FROM users WHERE id = ?", user)
    totalHoldings = userBalance[0]["cash"] + totalValueSum

    for dict in stockList:
        dict["price"] = usd(dict["price"])
        dict["total_value"] = usd(dict["total_value"])

    return render_template("index.html", stockList=stockList, userBalance=usd(userBalance[0]['cash']), totalHoldings=usd(totalHoldings))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    # complete purchase
    if request.method == "POST":
        # make sure stock and quantity are added
        if not request.form.get("symbol"):
            return apology("Must include stock symbol")

        if not request.form.get("quantity"):
            return apology("Must add quantity")

        quantity = int(request.form.get("quantity"))
        if quantity < 1:
            return apology("Quantity must be more than 0")

        # look up stock's current price
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        stockInfo = lookup(symbol)
        currentPrice = stockInfo["price"]
        totalPrice = quantity * int(currentPrice)

        # check how much money the user has
        user = session.get("user_id")
        userBalanceDict = db.execute("SELECT cash FROM users WHERE id = ?", user)
        userBalance = userBalanceDict[0]['cash']
        print(userBalance)
            # if not enough, return an apology
        if totalPrice > userBalance:
            return apology("You need more money!")

        type = "bought"
        # add purchase info to table in finance.db
        db.execute("INSERT INTO transactions (user_id, symbol, price, quantity, total, type) VALUES (?, ?, ?, ?, ?, ?)", user, symbol, currentPrice, quantity, totalPrice, type)

        #update user's balance
        userBalance = userBalance - totalPrice
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userBalance, user)

        # return user to home page
    return index()


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = session.get("user_id")
    historyList = db.execute("SELECT type, symbol, price, date, time FROM transactions WHERE user_id = ? ORDER BY date DESC, time DESC", user)
    return render_template("history.html", historyList=historyList)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    #if get
    if request.method == "GET":
        return render_template("quote.html")

    # if post
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quotedStock = lookup(symbol)

        # give an error if stock isn't real
        if quotedStock == None:
            return apology("Enter a real stock, idiot")

        # convert price to USD format
        quotedStock["price"] = usd(quotedStock["price"])

        return render_template("quoted.html", quotedStock = quotedStock)

    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # if reached by get, display register page
    if request.method == "GET":
        return render_template("register.html")

    # if user reached this page by post
    if request.method == "POST":
        # check for a username
        if not request.form.get("username"):
            return apology("must provide unique username", 403)

        # check if that username already exists
        username = request.form.get("username")
        usernameCheck = db.execute("SELECT COUNT(username) FROM users WHERE username = ?", (username))
        if usernameCheck[0]["COUNT(username)"] > 0:
            return apology("username already exists", 403)

        # confirm password was entered
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # confirm passwords match
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("passwords must match", 403)

        # save username and password hash to user database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password, salt_length=len(password)))
        return redirect("/login")

    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")

    if request.method == "POST":
         # make sure stock and quantity are added
        if not request.form.get("symbol"):
            return apology("Must include stock symbol")

        if not request.form.get("quantity"):
            return apology("Must add quantity")

        quantity = int(request.form.get("quantity"))
        if quantity < 1:
            return apology("Quantity must be more than 0")

        # look up stock's current price
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        stockInfo = lookup(symbol)
        currentPrice = stockInfo["price"]
        totalPrice = quantity * int(currentPrice)

        # add purchase info to table in finance.db
        user = session.get("user_id")
        type = "sold"
        db.execute("INSERT INTO transactions (user_id, symbol, price, quantity, total, type) VALUES (?, ?, ?, ?, ?, ?)", user, symbol, currentPrice, quantity, totalPrice, type)

        #update user's balance
        userBalanceDict = db.execute("SELECT cash FROM users WHERE id = ?", user)
        userBalance = userBalanceDict[0]['cash'] + totalPrice
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userBalance, user)

        return index()
