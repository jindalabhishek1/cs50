#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while((height < 1) || (height > 8));
    for (int i = height; i > 0; i--)
    {
        for (int j = 0; j < height; j++)
        {
            if(j < (i - 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}