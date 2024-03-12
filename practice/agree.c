#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt user to agree
    char c = get_char("do u agree? ");

    //check if they agree
    if (c == 'Y' || c == 'y')
    {
        printf("this bitch agrees\n");
    }

    else if (c == 'N' || c == 'n')
    {
        printf("this bitch doesn't agree\n");
    }

    else
    {
        printf("pick y or n bitch\n");
    }

}