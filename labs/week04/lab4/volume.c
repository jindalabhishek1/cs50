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

    // Open files and determincde scaling factor
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

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    int16_t sample = 0;

    int num = fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    printf("Bytes read: %d\n", num);
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    // fscanf and fprintf will not work as we are reading the raw bytes from the file, no the content from the file
    // for (int i = 0; i < HEADER_SIZE; i++)
    // {
    //     // fscanf(input, "%hhu", &header_byte);
    //     fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    //     // printf("%hhu", header_byte);
    //     // printf("%d:", i+1);
    //     // fprintf(output, "%hhu", header_byte);
    //     fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);
    // }
    // fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    // fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file

    int pos = ftell(input);
    printf("Current position: %d\n", pos);
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // fscanf(input, "%hd", &sample);

        // fprintf(output, "%hd", sample);
        // pos = ftell(input);
        // printf("Current position: %d\n", pos);
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    }
    // int pos = ftell(input);
    // printf("Current position: %d\n", pos);
    // while (feof(input) == 0)
    // {
    //     pos = ftell(input);
    //     printf("Current position: %d\n", pos);
    //     fread(&sample, sizeof(int16_t), 1, input);
    //     fwrite(&sample, sizeof(int16_t), 1, output);
    // }

    // Close files
    fclose(input);
    fclose(output);
}
