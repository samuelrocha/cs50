#include <stdio.h>
#include <cs50.h>

void print_map(int height, int width);
void type_hash(int expression);
int allowed_number();

int main()
{
    int height, width;
    height = allowed_number();
    width = (height * 2) + 2;
    print_map(height, width);
}

int allowed_number()
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

void print_map(int height, int width)
{
    int count = height + 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < height)
            {
                if (i + j >= height - 1)
                {
                    type_hash(1);
                }
                else
                {
                    type_hash(0);
                }

            }
            else if (j >= height && j < height + 2)
            {
                type_hash(0);
            }
            else
            {
                if (i + j <= count)
                {
                    type_hash(1);
                }
                else
                {
                    break;
                }
            }
        }
        count += 2;
        printf("\n");
    }
}

void type_hash(int expression)
{
    if (expression)
    {
        printf("#");
    }
    else
    {
        printf(" ");
    }
}