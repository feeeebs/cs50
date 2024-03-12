from cs50 import get_string
import sys


def main():
    # get input
    card_number = get_input()

    # check if valid
    validity = check_valid(card_number)
    if validity == "INVALID":
        print(f"{validity}")
        sys.exit(1)

    # check what type of card it is
    result = check_type(card_number)

    # print result
    print(f"{result}")


# function collects credit card number from user
def get_input():
    # ask user for input, checking to make sure it fits parameters
    while True:
        user_number = get_string("Number: ")
        if len(user_number) in [13, 15, 16]:
            return user_number
        else:
            print("INVALID")
            sys.exit(1)


# function outputs valid or invalid
def check_valid(number):
    multipliers = []
    pointy_guy = len(number) - 2
    while pointy_guy >= 0:
        multipliers.append(number[pointy_guy])
        pointy_guy -= 2

    # multiply all the numbers in multiplers by two
    new_multipliers = []
    list_length = len(multipliers)
    for i in range(list_length):
        integer = int(multipliers[i]) * 2
        if integer > 9:
            integer_as_string = str(integer)
            first_number = integer_as_string[0]
            second_number = integer_as_string[1]
            new_multipliers.append(int(first_number))
            new_multipliers.append(int(second_number))
        else:
            new_multipliers.append(integer)

    # split out any double digit numbers into single digits

    products_sum = sum(new_multipliers)

    adders = []
    pointy_guy = len(number) - 1
    while pointy_guy >= 0:
        adders.append(int(number[pointy_guy]))
        pointy_guy -= 2

    total_sum = sum(adders) + products_sum
    if total_sum % 10 == 0:
        return "VALID"
    else:
        return "INVALID"


# function outputs card type
def check_type(number):
    # AMEX - 15 digits and start with 34 or 37
    amex_slice = number[0:2]
    if amex_slice == "34" or amex_slice == "37" and len(number) == 15:
        return "AMEX"

    # MASTERCARD - 16 digits and start with 51, 52, 53, 54, 55
    mastercard_slice = number[0:2]
    if mastercard_slice in ["51", "52", "53", "54", "55"] and len(number) == 16:
        return "MASTERCARD"

    # VISA - 13 or 16 digits and start with 4
    visa_slice = number[0:1]
    if visa_slice == "4" and (len(number) == 13 or len(number) == 16):
        return "VISA"

    return "INVALID"


main()
