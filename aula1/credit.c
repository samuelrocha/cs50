#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    long int number, copy;
    int digits, rest, swap, sum, bank;
    sum = swap = digits = 0;
    do
    {
        number = get_long("Number: ");
    } while (number < 1);

    copy = number;
    while (number > 0)
    {
        rest = number % 10;
        number = number / 10;
        digits++;
        if (swap == 1)
        {
            swap = 0;
            rest = rest * 2;
            if(rest >= 10)
            {
                sum += (rest % 10) + (rest / 10);
            }
            else
            {
                sum += rest;
            }
        }
        else
        {
            swap = 1;
            sum += rest;
        }
    }
    if (sum % 10 == 0)
    {
        double x;
        if(digits == 13)
        {
            x = pow(10.0, 12.0);
            bank = copy / (long) x;
            if (bank == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 15)
        {
            x = pow(10.0, 13.0);
            bank = copy / (long) x;
            if (bank == 34 || bank == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 16)
        {
            x = pow(10.0, 15.0);
            bank = copy / (long) x;
            if (bank == 4)
            {
                printf("VISA\n");
            }
            else
            {
                x = pow(10.0, 14.0);
                bank = copy / (long) x;
                if (bank == 51 || bank == 52 || bank == 53 || bank == 54 || bank == 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}