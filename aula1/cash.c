#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float money;
    do
    {
        money = get_float("Chance owed: ");
    }
    while (!(money > 0));
    int cents = round(money * 100);
    int sum = 0;
    while (cents != 0)
    {
        if (cents >= 25)
        {
            cents = cents - 25;
            sum++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            sum++;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
            sum++;
        }
        else
        {
            cents = cents - 1;
            sum++;
        }
    }
    printf("%d\n", sum);
}