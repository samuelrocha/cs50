#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int p, pf, y;

    y = 0;
    do
    {
        p = get_int("Start size: ");
    }
    while (p < 9);
    do
    {
        pf = get_int("End size: ");
    }
    while (pf < p);

    while (p < pf)
    {
        y++;
        p += (p / 3) - (p / 4);
    }

    printf("Years: %d\n", y);
}