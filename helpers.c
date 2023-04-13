#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go through each row of image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int y = 0; y < width; y++)
        {
            // Set an variable to capture the entire value of selected pixel
            int c = (image[i][y].rgbtBlue + image[i][y].rgbtGreen
                     + image[i][y].rgbtRed);
            // Divide save value by 3.0 to compute average
            float d = c / 3.0;
            // Round the average
            int average = round(d);
            // Set all colors at selected pixed to average
            image[i][y].rgbtBlue = average;
            image[i][y].rgbtGreen = average;
            image[i][y].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Go through each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int y = 0; y < width; y++)
        {
            // Original amounts of red, green and blue
            int b = image[i][y].rgbtBlue;
            int g = image[i][y].rgbtGreen;
            int r = image[i][y].rgbtRed;

            // Sepia formula to calculate the new blue.
            float a1 = 0.272 * r;
            float a2 = 0.534 * g;
            float a3 = 0.131 * b;
            float a4 = a1 + a2 + a3;
            int a5 = round(a4);
            image[i][y].rgbtBlue = a5;

            // Sepia formula to calculate the new green.
            float b1 = 0.349 * r;
            float b2 = 0.686 * g;
            float b3 = 0.168 * b;
            float b4 = b1 + b2 + b3;
            int b5 = round(b4);
            int *pk1 = &b5;
            if (*pk1 > 255)
            {
                *pk1 = 255;
            }
            image[i][y].rgbtGreen = *pk1;

            // Sepia formula to calculate the new red.
            float c1 = 0.393 * r;
            float c2 = 0.769 * g;
            float c3 = 0.189 * b;
            float c4 = c1 + c2 + c3;
            int c5 = round(c4);
            int *pk2 = &c5;
            if (*pk2 > 255)
            {
                *pk2 = 255;
            }
            image[i][y].rgbtRed = *pk2;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int l = 0, counter = width - 1; l < width; l++)
        {
            // Set variable for half of the width (to stop swapping)
            int ha_wi = width / 2;

            // Set variables for all 3 colors
            int working_b = 0;
            int working_g = 0;
            int working_r = 0;

            // Set pointers for working variables
            int *pk_0 = &working_b;
            int *pk_1 = &working_g;
            int *pk_2 = &working_r;

            // Store last elements of rgbt in variable
            *pk_0 = image[i][l].rgbtBlue;
            *pk_1 = image[i][l].rgbtGreen;
            *pk_2 = image[i][l].rgbtRed;

            // Swap first element of rgbtBlue with last element
            image[i][l].rgbtBlue = image[i][counter].rgbtBlue;
            image[i][l].rgbtGreen = image[i][counter].rgbtGreen;
            image[i][l].rgbtRed = image[i][counter].rgbtRed;

            // Place stored element at new location in array
            image[i][counter].rgbtBlue = *pk_0;
            image[i][counter].rgbtGreen = *pk_1;
            image[i][counter].rgbtRed = *pk_2;

            // Decrement counter
            counter--;

            if (counter == ha_wi)
            {
                l = width;
            }

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Data structure to save colours from image
    typedef struct
    {
        int rgbtBlue;
        int rgbtGreen;
        int rgbtRed;
    }
    saved_colours[height + 1][width + 1];
    saved_colours stored_image;
    // Loop to fill saved_colours data structure with colour values from image
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            // Fill saved_colours data structure with colour values from image
            stored_image[i][y].rgbtBlue = image[i][y].rgbtBlue;
            stored_image[i][y].rgbtGreen = image[i][y].rgbtGreen;
            stored_image[i][y].rgbtRed = image[i][y].rgbtRed;
        }
    }

    // Compute colour
    for (int t = 0; t < height; t++)
    {
        for (int r = 0; r < width; r++)
        {
            // Take colourvalue of struct-grid
            int average_b = 0;
            int *pk_0 = &average_b;

            int average_g = 0;
            int *pk_1 = &average_g;

            int average_r = 0;
            int *pk_2 = &average_r;

            // Scan blue parts of grid
            *pk_0 += stored_image[t - 1][r - 1].rgbtBlue;
            *pk_0 += stored_image[t - 1][r].rgbtBlue;
            *pk_0 += stored_image[t - 1][r + 1].rgbtBlue;
            *pk_0 += stored_image[t][r - 1].rgbtBlue;
            *pk_0 += stored_image[t][r].rgbtBlue;
            *pk_0 += stored_image[t][r + 1].rgbtBlue;
            *pk_0 += stored_image[t + 1][r - 1].rgbtBlue;
            *pk_0 += stored_image[t + 1][r].rgbtBlue;
            *pk_0 += stored_image[t + 1][r + 1].rgbtBlue;

            // Scan green parts of grid
            *pk_1 += stored_image[t - 1][r - 1].rgbtGreen;
            *pk_1 += stored_image[t - 1][r].rgbtGreen;
            *pk_1 += stored_image[t - 1][r + 1].rgbtGreen;
            *pk_1 += stored_image[t][r - 1].rgbtGreen;
            *pk_1 += stored_image[t][r].rgbtGreen;
            *pk_1 += stored_image[t][r + 1].rgbtGreen;
            *pk_1 += stored_image[t + 1][r - 1].rgbtGreen;
            *pk_1 += stored_image[t + 1][r].rgbtGreen;
            *pk_1 += stored_image[t + 1][r + 1].rgbtGreen;

            // Scan red parts of grid
            *pk_2 += stored_image[t - 1][r - 1].rgbtRed;
            *pk_2 += stored_image[t - 1][r].rgbtRed;
            *pk_2 += stored_image[t - 1][r + 1].rgbtRed;
            *pk_2 += stored_image[t][r - 1].rgbtRed;
            *pk_2 += stored_image[t][r].rgbtRed;
            *pk_2 += stored_image[t][r + 1].rgbtRed;
            *pk_2 += stored_image[t + 1][r - 1].rgbtRed;
            *pk_2 += stored_image[t + 1][r].rgbtRed;
            *pk_2 += stored_image[t + 1][r + 1].rgbtRed;

            // Caluculate average
            *pk_0 = *pk_0 / 9;
            *pk_1 = *pk_1 / 9;
            *pk_2 = *pk_2 / 9;

            image[t][r].rgbtBlue = *pk_0;
            image[t][r].rgbtGreen = *pk_1;
            image[t][r].rgbtRed = *pk_2;

            *pk_0 = 0;
            *pk_1 = 0;
            *pk_2 = 0;
        }
    }
    return;
}
