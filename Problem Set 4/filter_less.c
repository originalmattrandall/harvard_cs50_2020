#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Method prototypes
int limit_value(int value, int max);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // When the values already match, we can skipp them as no conversion is required
            if (image[i][j].rgbtBlue == image[i][j].rgbtGreen && image[i][j].rgbtBlue == image[i][j].rgbtRed)
            {
                continue;
            }

            // convert the colors to grayscale
            int avg = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);

            // Convert the current image positions color values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the sepia values from the original colors
            int sepia_blue = limit_value(round((0.272 * (float)image[i][j].rgbtRed) + (0.534 * (float)image[i][j].rgbtGreen) + (0.131 * (float)image[i][j].rgbtBlue)), 255);
            int sepia_green = limit_value(round((0.349 * (float)image[i][j].rgbtRed) + (0.686 * (float)image[i][j].rgbtGreen) + (0.168 * (float)image[i][j].rgbtBlue)), 255);
            int sepia_red = limit_value(round((0.393 * (float)image[i][j].rgbtRed) + (0.769 * (float)image[i][j].rgbtGreen) + (0.189 * (float)image[i][j].rgbtBlue)), 255);

            // Convert the current image positions color values
            image[i][j].rgbtBlue = sepia_blue;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtRed = sepia_red;
        }
    }
}

// Return a value up to a maximum number provided.
int limit_value(int value, int max)
{
    int result = value;

    if(result > max)
    {
        result = 255;
    }

    return result;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Set up a temp variable to hold the rgb colors to swap and reflect
    // Three primary colors to store so we need a temp var of 3 bytes
    int rgbTemp[3];

    // Begin looping through the image pixels to swap them around
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Store the current values in the temp variable
            rgbTemp[0] = image[i][j].rgbtBlue;
            rgbTemp[1] = image[i][j].rgbtRed;
            rgbTemp[2] = image[i][j].rgbtGreen;

            // Swap the pixels to the opposite side
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            // Reassign the pixels on the other side with the ones held in the temp variable
            image[i][width - j - 1].rgbtBlue = rgbTemp[0];
            image[i][width - j - 1].rgbtRed = rgbTemp[1];
            image[i][width - j - 1].rgbtGreen = rgbTemp[2];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a copy of the array to not modify the original values while calculating the sums of each color
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Begin looping through the images pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store the sum of each colors blur level
            int sumBlue = 0;
            int sumRed = 0;
            int sumGreen = 0;
            float pixelCount = 0.0;

            // Begin looping through the nearest pixels closest to the current pixel we are at
            for (int h = -1; h < 2; h++)
            {
                // Verify that height is not out of bounds
                int currentPixelHeight = i + h;
                if (currentPixelHeight < 0 || currentPixelHeight > height - 1)
                {
                    continue; // Return to start of loop. (the word continue is kind of missleading)
                }

                // Verify that wudth is not out of bounds
                for (int w = -1; w < 2; w++)
                {
                    int currentPixelWidth = j + w;
                    if (currentPixelWidth < 0 || currentPixelWidth > width - 1)
                    {
                        continue; // Return to start of loop. (the word continue is kind of missleading)
                    }

                    // Add up the sum of the surrounding pixels
                    sumBlue += copy[currentPixelHeight][currentPixelWidth].rgbtBlue;
                    sumRed += copy[currentPixelHeight][currentPixelWidth].rgbtRed;
                    sumGreen += copy[currentPixelHeight][currentPixelWidth].rgbtGreen;

                    // Add up the total number of times we iterated to get a proper average
                    pixelCount++;
                }
            }

            // Blur the images pixels using the average of each color
            image[i][j].rgbtBlue = round(sumBlue / pixelCount);
            image[i][j].rgbtRed = round(sumRed / pixelCount);
            image[i][j].rgbtGreen = round(sumGreen / pixelCount);
        }
    }
}
