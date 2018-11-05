#include <cs50.h>
#include <stdio.h>

int height(void);
void pyramids(int n);

int main(void)
{
    int n = height();
    pyramids(n);
}

int height(void)
{
    int n;
    do
    {
        printf("Height: ");
        n = get_int();
    }
    while (n < 0 || n > 23);
    return n;
}

void pyramids(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j >= n - 1 - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int j = 0; j < n; j++)
        {
            if (j <= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}