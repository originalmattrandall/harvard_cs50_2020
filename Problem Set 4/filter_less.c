#include "helpers.h"
#include "math.h"

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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
