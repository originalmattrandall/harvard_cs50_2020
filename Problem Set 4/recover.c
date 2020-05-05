#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// Method prototypes
bool is_jpeg_file(BYTE header[512]);

int main(int argc, char *argv[])
{
    // Ensure only 1 command line argument is passed in
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Attempt to open the file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    // Required variables (We set them up after we know the input args are all valid)
    BYTE header[512];
    size_t blockOfBytes;
    char outputFileName[8];
    FILE *outputFile = NULL;
    int totalImages = 0;

    do
    {
        blockOfBytes = fread(header, sizeof(BYTE), 512, inputFile);

        bool isJpegFile = is_jpeg_file(header);

        // Close the previous output file as a new one has been found
        if (isJpegFile && outputFile != NULL)
        {
            fclose(outputFile);
            totalImages++;
        }

        // jpeg found, open it and write it to a new file
        if (isJpegFile)
        {
            sprintf(outputFileName, "%03i.jpg", totalImages);
            outputFile = fopen(outputFileName, "w");
        }

        // Write to the file if its open
        if (outputFile != NULL)
        {
            fwrite(header, sizeof(BYTE), blockOfBytes, outputFile);
        }
    }
    while (blockOfBytes != 0 && !feof(inputFile));

    // Close the output file (recovered file)
    fclose(outputFile);

    // Close the initial input file
    fclose(inputFile);

}

bool is_jpeg_file(BYTE header[512])
{
    return header[0] == 0xff &&
           header[1] == 0xd8 &&
           header[2] == 0xff &&
           (header[3] & 0xf0) == 0xe0;
}
