# https://cs50.harvard.edu/x/2021/psets/1/cash/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int minimum_change(int change);

int main (void)
{
    // get chagned owed from user using get_float (positive values only)
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);


    // convert float to int (1 unit = 1 cent) with rounding, to avoid floating point imprecision
    int cents = round(dollars * 100);

    // print minimum number of coins using helper function
    printf("%i\n", minimum_change(cents));
}

int minimum_change(int cents)
{
    int cents_remaining = cents;
    int coin_count = 0;

    //dispense change in descending order of coins (in cents): 25, 10, 5, 1
    while (cents_remaining >= 25)
    {
        cents_remaining -= 25;
        coin_count ++;
    }

    while (cents_remaining >= 10)
    {
        cents_remaining -= 10;
        coin_count ++;
    }

    while (cents_remaining >= 5)
    {
        cents_remaining -= 5;
        coin_count ++;
    }

    while (cents_remaining >= 1)
    {
        cents_remaining -= 1;
        coin_count ++;
    }

    return coin_count;
}