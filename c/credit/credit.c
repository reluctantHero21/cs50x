# https://cs50.harvard.edu/x/2021/psets/1/credit/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

// prototypes for helper functions
int get_last_digit(long n);
long truncate(long n);
int length(long n);
int get_checksum(long cardNumber);
int get_firstTwoDigits(long cardNumber);
string get_cardtype(long cardNumber);

// MAIN
int main(void)
{
    // prompt user for a credit card number
    long cardNumber;
    cardNumber = get_long("Enter your credit card number: ");

    // determine cardNumber validibity based on checksum, then validate length and starting digits
    int checksum = get_checksum(cardNumber);

    if (get_last_digit(checksum) == 0)
    {
        printf("%s\n", get_cardtype(cardNumber));
    }
    else
    {
        printf("INVALID\n");
    }
}

// HELPER FUNCTIONS

// function that returns last digit of a number
int get_last_digit(long n)
{
    return n % 10;
}

// function that takes long n and returns n with the last digit truncated
long truncate(long n)
{
    long last_digit = n % 10;
    return (n - last_digit) / 10;
}

// function that returns the Luhn’s algorithm checksum for a given long integer
int get_checksum(long cardNumber)
{
    long remaining = cardNumber;
    int checksum = 0;
    int pos = 0; // position from last digit

    // creates checksum based on position from last digit to first digit
    while (remaining > 0)
    {
        // Case 1: last digit (and every second) - add that digit to the checksum
        if (pos % 2 == 0)
        {
            checksum += get_last_digit(remaining);
        }
        // Case 2: second-last digit (and every second) - add the digits of [the product of (digit x 2)]
        else
        {
            int product = get_last_digit(remaining) * 2;

            if (product < 10)
            {
                checksum += product;
            }
            else
            {
                checksum += get_last_digit(product);
                checksum += truncate(product);
            }
        }

        pos++;
        remaining = truncate(remaining);
    }
    return checksum;
}

int get_firstTwoDigits(long cardNumber)
{
    long remaining = cardNumber;

    //truncate until 2 digits left
    while (remaining > 99)
    {
        remaining = truncate(remaining);
    }

    return remaining;
}

// function that checks the validity of card number based on first two digits and length
string get_cardtype(long cardNumber)
{
    // MasterCard uses 16-digit numbers and starts with 51, 52, 53, 54, or 55
    if (get_firstTwoDigits(cardNumber) == 51 || get_firstTwoDigits(cardNumber) == 52 || get_firstTwoDigits(cardNumber) == 53
        || get_firstTwoDigits(cardNumber) == 54 || get_firstTwoDigits(cardNumber) == 55)
    {
        if (length(cardNumber) == 16)
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }

    // Visa uses 13- and 16-digit numbers and starts with 4
    else if (truncate(get_firstTwoDigits(cardNumber)) == 4)
    {
        if (length(cardNumber) == 13 || length(cardNumber) == 16)
        {
            return "VISA";
        }
        return "INVALID";
    }

    // AMEX uses 15-digit numbers and starts with 34 or 37
    else if (get_firstTwoDigits(cardNumber) == 34 || get_firstTwoDigits(cardNumber) == 37)
    {
        if(length(cardNumber) == 15)
        {
            return "AMEX";
        }
        return "INVALID";
    }

    // Catch case for all other (invalid)
    else
    {
        return "INVALID";
    }
}

int length(long n)
{
   long remaining = n;
   int count = 0;

   while (remaining > 0)
   {
       remaining = truncate(remaining);
       count++;
   }

   return count;
}
