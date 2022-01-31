// https://cs50.harvard.edu/x/2021/psets/2/caesar/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int rotate_char(char c, int k);

int main(int argc, string argv[])
{
    // error case 1: user enters invalid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // error case 2: not all characters of KEY are decimal digits
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // convert argument (key) to int
        int k = atoi(argv[1]);

        // error case 3: KEY is not a positive integer
        if (k <= 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            // prompt user to enter plaintext
            string plaintext = get_string("plaintext:  ");

            // print the ciphertext
            printf("ciphertext: ");

            // for each character in the string, print the rotated character using helper function
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                printf("%c", rotate_char(plaintext[i], k));
            }
            printf("\n");
        }
    }
}

// function that rotates char C by K positions, if char c is alpha (lower or upper case letter). Returns ASCII int value of the rotated character. Assumes positive K
int rotate_char(char c, int k)
{
    int rotated = c;
    if (islower(c))
    {
        rotated = c + k;

        // if out of bound, bring valud back to range of 'a' to 'z'
        while (rotated > 'z')
        {
            rotated -= 26;
        }
    }
    else if (isupper(c))
    {
        rotated = c + k;

        // if out of bound, bring valud back to range of 'A' to 'Z'
        while (rotated > 'Z')
        {
            rotated -= 26;
        }
    }
    return rotated;
}