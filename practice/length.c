#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    //prompt for user's name
    string name = get_string("Name: ");

    //count number of characters until null
    int n = 0;
    while (name[n] != '\0')
    {
        n++;
    }
    printf("%i\n", n);
}