#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int msg, valid, key;
    string plaintext, ciphertext;

    valid = 1;
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                valid = 0;
            }
        }

        if (valid)
        {
            key = strtol(argv[1], NULL, 10);
            plaintext = get_string("plaintext: ");
            ciphertext = plaintext;
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                if (isupper(plaintext[i]))
                {
                    ciphertext[i] = (plaintext[i] + key - 'A') % 26 + 'A';
                }
                else if (islower(plaintext[i]))
                {
                    ciphertext[i] = (plaintext[i] + key - 'a') % 26 + 'a';
                }
            }
            printf("ciphertext: %s\n", ciphertext);
            msg = 0;
        }
        else
        {
            printf("./caesar key\n");
            msg = 1;
        }
    }
    else
    {
        printf("./caesar key\n");
        msg = 1;
    }
    return msg;
}