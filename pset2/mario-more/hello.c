#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask user for name and store it in a variable
    string answer = get_string("What's your name? ");
    //print name that the user entered
    printf("hello, %s\n", answer);
}