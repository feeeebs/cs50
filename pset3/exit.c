#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }

    printf("hello, %s\n", argv[1]);
    return 0; //computer does this by default if it works but good practice to call it out
}