// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copying header from input file to output file

    uint8_t Header[HEADER_SIZE];
    
    fread (Header, HEADER_SIZE, 1, input);
    fwrite (Header, HEADER_SIZE, 1, output);
    
    
    // Reading samples from input file and write updated data to output file

    int16_t Buffer;
    
    while (fread (&Buffer, sizeof(int16_t), 1, input))
    {
        //Update Volume by the given factor
        Buffer = Buffer * factor;
        fwrite (&Buffer, sizeof(int16_t), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
