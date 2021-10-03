#include <cs50.h>
#include <stdio.h>

int minutes(void);
void bottles(int n);
int main(void)
{
    int n = minutes();
    bottles(n);
}

int minutes(void)
{
    printf("Minutes: ");
    return get_int();
}

void bottles(int n)
{
    printf("Bottles: %i\n", n * 12);
}