from cs50 import get_int


def main():
    # get input from user
    number = get_number()

    # print
    print_hashes(number)


def get_number():
    while True:
        number = get_int("Number: ")
        if number >= 1 and number <= 8:
            return number


def print_hashes(number_of_hashes):
    spaces = 1

    for i in range(number_of_hashes):
        print(" " * (number_of_hashes - spaces), end="")
        print("#" * spaces, end="")
        print("  ", end="")
        print("#" * spaces)
        spaces += 1


main()
