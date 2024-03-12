#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const int MINE = 2;
    int points = get_int("How many points did you lose? ");

    if (points < MINE)
    {
        printf("you lost fewer points than me!\n");
    }
    else if (points > MINE)
    {
        printf("you lost more points than me!\n");
    }
    else
    {
        printf("you lost the same amount as me!\n");
    }
}