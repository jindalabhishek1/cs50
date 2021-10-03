#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    int change_cents = round(change * 100);
    // printf("Cents: %i\n", change_cents);
    int quaters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;
    int temp_change = change_cents;
    int number_of_coins = 0;
    while (temp_change != 0)
    {
        // printf("Change = %i\n",temp_change);
        if (temp_change >= quaters)
        {
            temp_change = temp_change - quaters;
            number_of_coins ++;
            continue;
        }
        if (temp_change >= dimes)
        {
            temp_change = temp_change - dimes;
            number_of_coins ++;
            continue;
        }
        if (temp_change >= nickels)
        {
            temp_change = temp_change - nickels;
            number_of_coins ++;
            continue;
        }
        if (temp_change >= pennies)
        {
            temp_change = temp_change - pennies;
            number_of_coins ++;
            continue;
        }
    }
    printf("%i\n", number_of_coins);
}