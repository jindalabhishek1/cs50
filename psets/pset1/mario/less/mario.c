#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // getting height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

    // looping rows
    for (int i = height; i > 0; i--)
    {
        // looping columns
        for (int j = 0; j < height; j++)
        {
            if (j < (i - 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // adding new line at the end of each row
        printf("\n");
    }
}