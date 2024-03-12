#include <stdio.h>
#include<cs50.h>

void meow(int n);

int main(void)
{
    int number = get_int(" how many meows? ");
    {
        meow(number);
    }
        //meow(3);
}















void meow(int n)
{
    for(int i = 0; i < n; i++)
    printf("meow\n");
}