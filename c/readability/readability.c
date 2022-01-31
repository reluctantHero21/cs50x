// https://cs50.harvard.edu/x/2021/psets/2/readability/

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // get user input
    string text = get_string("Text: ");

    // calculate average number of letters and sentences per 100 words
    float l = (float) count_letters(text) / count_words(text) * 100;
    float s = (float) count_sentences(text) / count_words(text) * 100;

    // calculate Coleman-Liau index
    float index = 0.0588 * l - 0.296 * s - 15.8;
    printf("%f\n", index);

    // calculate and print grade
    int grade = round(index);

    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// count letters of a string by iterating through each character
int count_letters(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count ++;
        }
    }

    return count;
}

// count words (assume no double spaces and text does not begin nor end with a space)
int count_words(string text)
{
    int count = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count ++;
        }
    }

    return count;
}

// count sentences (assume no periods within single sentence, and all sentences end with single period, exclamation mark or question mark)
int count_sentences(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count ++;
        }
    }

    return count;
}