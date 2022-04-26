#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;
BYTE buffer[512];
FILE *newfile = NULL;


int main(int argc, char *argv[])
{

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE        For example: ./recover card.raw\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file for reading.\n");
        return 2;
    }
    int i = 0;
    char filename[8];
    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", i);
            newfile = fopen(filename, "w");
            i++;
        }
        if (i > 0)
        {
            fwrite(&buffer, 1, BLOCK_SIZE, newfile);
        }
    }
    fclose(file);
    fclose(newfile);
    return 0;
}