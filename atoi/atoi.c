#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int length);
int chartoint(char letter);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, strlen(input)));
}

int convert(string input, int length)
{
    if (length == 1)
    {
        //printf("Returning: %c", input[0]);
        return chartoint(input[0]);
    }

    int integer = chartoint(input[length - 1]);
    length--;

return integer + (convert(input, length) * 10);

}

int chartoint(char letter)
{
    switch (letter)
        {
            case '1':
                return 1;
                break;

            case '2':
                return 2;
                break;

            case '3':
                return 3;
                break;

            case '4':
                return 4;
                break;

            case '5':
                return 5;
                break;

            case '6':
                return 6;
                break;

            case '7':
                return 7;
                break;

            case '8':
                return 8;
                break;

            case '9':
                return 9;
                break;

            default: // 0
                return 0;
                break;
        }
}