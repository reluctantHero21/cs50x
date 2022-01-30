// https://cs50.harvard.edu/x/2021/psets/1/mario/more/

#include <cs50.h>
#include <stdio.h>

void print_hashtag(int n);
void print_space(int n);

int main(void)
{
    // Get pyramid size (valid input is between 1 and 8)
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print pyramid

    for (int i = 0; i < height; i++)
    {
        //print blank space
        print_space(height - i - 1);

        //print hashtag (left half)
        print_hashtag(i + 1);

        //print 2 spaces
        printf("  ");

        //print hastag (right half)
        print_hashtag(i + 1);

        //print line break
        printf("\n");
    }

}

//helper function that prints n number of "#"
void print_hashtag(int n)
{
    for (int i = 0; i < n ; i++)
    {
        printf("#");
    }
}

//helper function that prints n number of spaces
void print_space(int n)
{
    for (int i = 0; i < n ; i++)
    {
        printf(" ");
    }
}
