// https://cs50.harvard.edu/x/2022/psets/4/recover/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open raw disk image
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // define variables for output file, image found (bool), image count, buffer
    FILE *output;
    int JPEG_found = 0; // this is a bool to indicate whether a JPEG was found
    int JPEG_count = 0;
    BYTE *buffer = malloc(BLOCK_SIZE);

    //read buffer block by block until end of input file
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        //Find JPEG usign first 4 hex values (header)
        if (
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            JPEG_found = 1;

            //generate file name xxx.jpg
            char *filename = malloc(sizeof(char) * 8);
            sprintf(filename, "%03d.jpg", JPEG_count);

            //create new file pointer and assign output to new file
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            JPEG_count ++;
        }

        if (JPEG_found == 1) //this condition skips the beginning of the raw input (not JPEG)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    free(buffer);
}
