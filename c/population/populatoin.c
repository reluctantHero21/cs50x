// https://cs50.harvard.edu/x/2021/labs/1/population/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end <= start);

    // Calculate number of years until we reach threshold
    int current = start;
    int years = 0;

	do
	{
		int born = current / 3;
		int died = current / 4;
		current = current + born - died;
		years++;
	}
	while (current < end);

    // Print number of years
    printf("Years: %i\n", years);
}