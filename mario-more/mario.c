#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <  1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        for (int n = height; n >= i; n--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
             printf("#");
        }
        printf("  ");
        
        for (int y = 0; y <= i; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}

