// https://cs50.harvard.edu/x/2022/psets/4/filter/less/

#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create 8-bit unsigned int (size: BYTE) to store average of RGB values
    uint8_t average = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // calculate average RGB value
            average = (int) round((image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3.0);

            // re-write RGB values as the average
            image[y][x].rgbtBlue = average;
            image[y][x].rgbtGreen = average;
            image[y][x].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // create 8-bit unsigned integers (size: BYTE) to store original RGB values and sepia values
    uint16_t sepiaRed = 0;
    uint16_t sepiaGreen = 0;
    uint16_t sepiaBlue = 0;
    uint8_t originalRed = 0;
    uint8_t originalGreen = 0;
    uint8_t originalBlue = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // get original RGB values
            originalRed = image[y][x].rgbtRed;
            originalGreen = image[y][x].rgbtGreen;
            originalBlue = image[y][x].rgbtBlue;

            // calculate sepia values
            sepiaRed = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // cap sepia values to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // re-write RGB values as the sepia values
            image[y][x].rgbtBlue = sepiaBlue;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the original image
    RGBTRIPLE(*imageCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            imageCopy[y][x].rgbtBlue = image[y][x].rgbtBlue;
            imageCopy[y][x].rgbtGreen = image[y][x].rgbtGreen;
            imageCopy[y][x].rgbtRed = image[y][x].rgbtRed;
        }
    }

    //change image to the reflection of the copy
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x].rgbtBlue = imageCopy[y][width - x - 1].rgbtBlue;
            image[y][x].rgbtGreen = imageCopy[y][width - x - 1].rgbtGreen;
            image[y][x].rgbtRed = imageCopy[y][width - x - 1].rgbtRed;
        }
    }

    free(imageCopy);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the original image
    RGBTRIPLE(*imageCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            imageCopy[y][x].rgbtBlue = image[y][x].rgbtBlue;
            imageCopy[y][x].rgbtGreen = image[y][x].rgbtGreen;
            imageCopy[y][x].rgbtRed = image[y][x].rgbtRed;
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // initialize temporary variables to store the blurred pixel
            float c = 0;
            uint16_t avgBlue = 0;
            uint16_t avgGreen = 0;
            uint16_t avgRed = 0;

            for (int a = (y - 1); a <= (y + 1); a++)
            {
                for (int b = (x - 1); b <= (x + 1); b++)
                {
                    if (a >= 0 && b >= 0 && a < height && b < width)
                    {
                        avgBlue += imageCopy[a][b].rgbtBlue;
                        avgGreen += imageCopy[a][b].rgbtGreen;
                        avgRed += imageCopy[a][b].rgbtRed;
                        c++;
                    }
                }
            }

            //re-write pixels in original image to the average blurred pixel
            image[y][x].rgbtBlue = (int) round(avgBlue / c);
            image[y][x].rgbtGreen = (int) round(avgGreen / c);
            image[y][x].rgbtRed = (int) round(avgRed / c);
        }
    }

    free(imageCopy);
    return;
}
