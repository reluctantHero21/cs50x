// https://cs50.harvard.edu/x/2021/psets/2/substitution/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int get_letterpos(char c);

int main(int argc, string argv[])
{
    // error case 1: user enters invalid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        string key = argv[1];

        // error case 2: key is not 26 characters
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // error case 3: key is not all alpha
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (isalpha(key[i]) == 0)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }

        // error case 4: duplicate characters in key
        int keysum = 0;
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            keysum += get_letterpos(key[i]);
        }
        if (keysum != 325)
        // sum of get_letterpos for the entire alphabet is 326
        {
            printf("Usage: ./substitution key (each chatarter must be unique)\n");
            return 1;
        }

        // prompt user to enter plaintext
        string plaintext = get_string("plaintext:  ");

        // print the ciphertext
        printf("ciphertext: ");

        // for each character in the string, print the substituted character using helper function
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            char c = plaintext[i];

            // if character is not alpha, print the character
            if (isalpha(c) == 0)
            {
                printf("%c", c);
            }
            else
            {
                // get the index of the plaintext character in order to retrieve corresponding cipher character
                int pos = get_letterpos(c);

                if (islower(c))
                {
                    printf("%c", tolower(key[pos]));
                }
                else if (isupper(c))
                {
                    printf("%c", toupper(key[pos]));
                }
                else
                {
                    return 1;
                }
            }
        }
        printf("\n");
        return 0;
    }
}


// function that returns the alphabetical position of an alphabetical character
int get_letterpos(char c)
{
    if (islower(c))
    {
        return (c - 'a');
    }
    else if (isupper(c))
    {
        return (c - 'A');
    }
    else
    {
        return 0;
    }
}