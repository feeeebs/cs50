#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get height of pyramid from the user (between 1 and 8)
    int height;
    do
    {
        height = get_int("How tall should the pyramid be? ");
    }
    while (height <= 0 || height >= 9);


    //create pyramid
    //spaces
    int s = height - 1;

    for (int i = 0; i < height; i++)
    {
        //left side
        //spaces
        if (height - i != 0)
        {
            for (int b = s; b > 0; b--)
            {
                printf(" ");
            }
        }

        //hashes
        for (int r = 0; r < height; r++)
        {
            if (i >= r)
            {
                printf("#");
            }
        }

        //center gap
        printf("  ");

        //right side
        for (int j = 0; j < height; j++)
        {
            if (i >= j)
            {
                printf("#");
            }
        }

        //new line
        printf("\n");
        //update spaces
        s--;
    }
}