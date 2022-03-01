#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining a datatype BYTE to represent a single byte
typedef uint8_t BYTE;

// Funtion for getting output file names
char *get_output_filename(int);

int main(int argc, char *argv[])
{
    // checking if only one argument is passed
    if (argc != 2)
    {
        printf("Usage: ./recover [infile]\n");
        return 1;
    }

    // getting the input file name
    char *inFile = argv[1];

    // opening the input file
    FILE *inPtr = fopen(inFile, "r");

    // checking if the file is opened
    if (inPtr == NULL)
    {
        printf("Could not open %s.\n", inFile);
        return 1;
    }

    // declaring a buffer to store the file contents
    BYTE *buffer = calloc(512, sizeof(BYTE));

    // imageCount variable to keep track of the number of images
    int imageCount = 0;

    // newFile variable to keep track of if a new file is to be created
    int newFile = 0;

    // Setting a pointer to the output file
    FILE *outPtr = NULL;

    // reading the file contents
    while (fread(buffer, sizeof(BYTE), 512, inPtr) == 512)
    {
        // checking if the first 3 bytes of the buffer match with the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // Checking if the forth byte is starting with 0xe
            if (buffer[3] >= 0xe0 && buffer[3] <= 0xef)
            {
                // if we get a valid JPEG signature, we create a new file and close the previous one
                if (newFile)
                {
                    FILE *prevOutPtr = outPtr;
                    fclose(prevOutPtr);
                    newFile = 0;
                }
                newFile = 1;

                // getting the output file name
                char *outFile = get_output_filename(imageCount);

                // opening the output file
                outPtr = fopen(outFile, "w");

                // free the space for output file name
                free(outFile);

                // writing the buffer to the output file
                fwrite(buffer, sizeof(BYTE), 512, outPtr);

                // incrementing the image count
                imageCount++;
            }
        }
        /**
         * @brief If the signature doesn't match to the JPEG signature,
         * Scenario 1: if the image is continued to the next buffer, we write the buffer to the output file
         * Scenario 2: if the image is not started, we skip the buffer
         */
        else
        {
            if (newFile)
            {
                fwrite(buffer, sizeof(BYTE), 512, outPtr);
            }
        }

    }
    printf("Image Count: %d\n", imageCount);

    // closing the last output file
    fclose(outPtr);

    // closing the input file
    fclose(inPtr);

    // freeing the buffer
    free(buffer);
    return 0;
}

// function to get the output file name
char *get_output_filename(int imageCount)
{
    // declaring a buffer to store the output file name
    char *outFile = calloc(8, sizeof(char));

    // if the image count is less than 10, we add "00" to the output file name
    if (imageCount >= 0 && imageCount < 10)
    {
        sprintf(outFile, "00%i.jpg", imageCount);
    }
    // if the image count is 2 digits, we add "0" to the output file name
    else if (imageCount >= 10 && imageCount < 100)
    {
        sprintf(outFile, "0%i.jpg", imageCount);
    }
    // if the image count more than 2 digits, we add nothing to the file name
    else
    {
        sprintf(outFile, "%i.jpg", imageCount);
    }
    return outFile;
}