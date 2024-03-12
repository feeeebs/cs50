#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float x = get_float("x: ");
    float y = get_float("y: ");

    //Dive x by y
    float z = x / y;

    printf("%.20f\n", z);
}