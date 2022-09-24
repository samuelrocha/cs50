#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int msg, length, valid;
    string plaintext, ciphertext;
    msg = 0;
    valid = 1;

    if (argc == 2)
    {
        length = strlen(argv[1]);
        if (length == 26)
        {
            for (int i = 0; i < length; i++)
            {
                if (!isalpha(argv[1][i]))
                {
                    printf("Key must only contain alphabetic characters.\n");
                    valid = 0;
                    msg = 1;
                }
                for (int j = 0; j < i; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        printf("Key must not contain repeated characters.\n");
                        valid = 0;
                        msg = 1;
                        break;
                    }
                }
                if (!valid)
                {
                    break;
                }
                argv[1][i] = toupper(argv[1][i]);
            }

            if (valid)
            {
                plaintext = get_string("plaintext: ");
                ciphertext = plaintext;
                for (int i = 0, n = strlen(plaintext); i < n; i++)
                {
                    if (islower(plaintext[i]))
                    {
                        ciphertext[i] = tolower(argv[1][(plaintext[i] - 'a') % 26]);
                    }
                    else if (isupper(plaintext[i]))
                    {
                        ciphertext[i] = argv[1][(plaintext[i] - 'A') % 26];
                    }
                }
                printf("ciphertext: %s\n", ciphertext);
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            msg = 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        msg = 1;
    }
    return msg;
}