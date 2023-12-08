#include "helpers.h"
#include <math.h>

// graustufen
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // für jeden pixel des bildes -> verschachtelte for-schleife
    // "zeile"
    for (int i = 0; i < height; i++)
    {
        // "spalte"
        for (int j = 0; j < width; j++)
        {
            int rgbt = round((image[i][j].rgbtBlue +
                              image[i][j].rgbtGreen +
                              image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = rgbt;
        }
    }
    return;
}

// sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // für jeden pixel des bildes -> verschachtelte for-schleife
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // setze sepia rgb werte für Rot Grün & Blau
            int sepiaB = round(.272 * image[i][j].rgbtRed +
                               .534 * image[i][j].rgbtGreen +
                               .131 * image[i][j].rgbtBlue);

            int sepiaG = round(.349 * image[i][j].rgbtRed +
                               .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);

            int sepiaR = round(.393 * image[i][j].rgbtRed +
                               .769 * image[i][j].rgbtGreen +
                               .189 * image[i][j].rgbtBlue);

            // setze sepiaB
            if (sepiaB > 255) {
                image[i][j].rgbtBlue = 255;
            } else {
                image[i][j].rgbtBlue = sepiaB;
            }

            // setze sepiaG
            if (sepiaG > 255) {
                image[i][j].rgbtGreen = 255;
            } else {
                image[i][j].rgbtGreen = sepiaG;
            }

            // setze sepia R
            if (sepiaR > 255) {
                image[i][j].rgbtRed = 255;
            } else {
                image[i][j].rgbtRed = sepiaR;
            }
        }
    }
    return;
}

// horizontal
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }

        else if (width % 2 != 0)
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
    }
    return;
}

// blur
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumB = 0;
            float sumG = 0;
            float sumR = 0;
            float counter = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }

                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    sumB += image[i + r][j + c].rgbtBlue;
                    sumG += image[i + r][j + c].rgbtGreen;
                    sumR += image[i + r][j + c].rgbtRed;
                    counter++;
                }
            }

            temp[i][j].rgbtBlue = round(sumB / counter);
            temp[i][j].rgbtGreen = round(sumG / counter);
            temp[i][j].rgbtRed = round(sumR / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }

    }
    return;
}