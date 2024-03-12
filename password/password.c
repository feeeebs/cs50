// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upper, lower, digit, symbol = false;
    int length = strlen(password);

    //iterate through each char in the password to see if it's uppercase, lowercase, number, or symbol
    for (int i = 0; i < length; i++)
    {
        char c = password[i];
        if (isupper(c))
        {
            upper = true;
        }
        if (islower(c))
        {
            lower = true;
        }
        if (isdigit(c))
        {
            digit = true;
        }
        if (ispunct(c))
        {
            symbol = true;
        }
    }

    return (upper && lower && digit && symbol);

}