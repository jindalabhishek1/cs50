#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // geting height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));
    // keeping a track of lines/levels in pyramid
    for (int i = height; i > 0; i--)
    {
        // right alligned pyramid
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

        // space between both the pyramids
        printf("  ");

        // left alligned pyramid
        for (int j = 0; j < height; j++)
        {
            if (j <= (height - i))
            {
                printf("#");
            }
        }
        // moving cursor to next line
        printf("\n");
    }
}