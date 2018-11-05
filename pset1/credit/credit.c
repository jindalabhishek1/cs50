#include <cs50.h>
#include <stdio.h>

long long int creditNum(void);
void checkCreditNum(long long int);
void checkCard(long long int, int);

int main(void)
{
    long long int n = creditNum();
    checkCreditNum(n);
}

long long int creditNum(void)
{
    printf("Number: ");
    return get_long_long();
}

void checkCreditNum(long long int n)
{
    long long int temp = n;
    int i = 0, sum1 = 0, sum2 = 0, s, r, a, totalSum;
    while (n != 0)
    {
        //r = n % (10 ^ i);
        s = n % 10;
        sum1 = sum1 + s;
        i++;
        n = n / 10;
        if (n != 0)
        {
            r = n % 10;
            r = r * 2;
            if (r > 9)
            {
                while (r != 0)
                {
                    a = r % 10;
                    sum2 = sum2 + a;
                    r = r / 10;
                }
            }
            else
            {
                sum2 = sum2 + r;
            }
            i++;
            n = n / 10;
        }
    }
    totalSum = sum1 + sum2;
    //printf("sum1 is : %i\n", sum1);
    //printf("sum2 is : %i\n", sum2);
    //printf("total sum is : %i\n", totalSum);
    //printf("i is : %i\n", i);
    if (totalSum % 10)
    {
        printf("INVALID\n");
    }
    else
    {
        checkCard(temp, i);
    }
}

void checkCard(long long int n, int i)
{
    //int startNum = n / 10000000000000;
    while (i != 2)
    {
        n = n / 10;
        i--;
        //printf("n : %lli\ni = %i\n", n, i);
    }
    string cardName;
    switch (n)
    {
        case 34:
        case 37:
            cardName = "AMEX";
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            cardName = "MASTERCARD";
            break;
        default:
            cardName = "VISA";
            break;
    }
    printf("%s\n", cardName);
    //printf("starting num is %lld\n", n);
}