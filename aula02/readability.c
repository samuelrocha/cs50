#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int ispuncf(char letter);
double averagesentences(int spaces, int points);
double averageletters(int spaces, int letters);

int main(void)
{
    int letters, spaces, points, grade;
    double index, average_letters, average_sentences;
    string text;

    letters = spaces = points = 0;
    text = get_string("Text: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            spaces++;
        }
        else if (ispuncf(text[i]))
        {
            points++;
        }
    }

    average_sentences = averagesentences(spaces, points);
    average_letters = averageletters(spaces, letters);

    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        grade = round(index);
        printf("Grade %d\n", grade);
    }

    return 0;
}

int ispuncf(char letter)
{
    int is;
    if (letter == '?' || letter == '!' || letter == '.')
    {
        is = 1;
    }
    else
    {
        is = 0;
    }
    return is;
}

double averagesentences(int spaces, int points)
{
    double average;
    average = (float) points / (spaces + 1);
    average = average * 100;
    return average;
}

double averageletters(int spaces, int letters)
{
    double average;
    average = (float) letters / (spaces + 1);
    average = average * 100;
    return average;
}