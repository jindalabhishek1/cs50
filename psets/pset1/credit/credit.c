#include <stdio.h>
#include <cs50.h>
#include <math.h>

int check_valid(long);
void credit_card_issuer(long, int);

int main(void)
{
    // Getting credit card number from user
    long credit_card_number = get_long("Number: ");

    // calling the check valid function
    // output will be size of credit card number if it is valid otherwise 0
    int size = check_valid(credit_card_number);

    if (size == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // checking which issuer issued the card
    credit_card_issuer(credit_card_number, size);

}

int check_valid(long number)
{
    int sum = 0;
    int temp = 0;
    int size = 0;
    while (number != 0)
    {
        size++;
        int digit = number % 10;
        if (temp == 1)
        {
            digit = digit * 2;
        }
        if (digit > 9)
        {
            while (digit != 0)
            {
                sum = sum + (digit % 10);
                digit = digit / 10;
            }
        }
        else
        {
            sum = sum + digit;
        }
        if (temp == 1)
        {
            temp = 0;
        }
        else
        {
            temp++;
        }
        number = number / 10;
        // printf("Sum: %d\n", sum);
        // printf("Number: %ld\n", number);
    }

    // printf("Sum: %d\n", sum);

    if ((sum % 10) == 0)
    {
        return size;
    }
    else
    {
        return 0;
    }
}

void credit_card_issuer(long number, int size)
{
    // printf("Size: %d\n", size);
    string issuer = "INVALID";
    int start = 0;
    // check amex
    if (size == 15)
    {
        start = number / pow(10, size - 2);
        if (start == 34 || start == 37)
        {
            issuer = "AMEX";
        }
    }
    if (size == 16)
    {
        start = number / pow(10, size - 2);
        if (start >= 51 && start <= 55)
        {
            issuer = "MASTERCARD";
        }
    }
    if (size == 13 || size == 16)
    {
        start = number / pow(10, size - 1);
        if (start == 4)
        {
            issuer = "VISA";
        }
    }
    // printf("Start: %d\n", start);
    printf("%s\n", issuer);
}