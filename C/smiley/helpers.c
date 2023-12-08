#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // verschachtelte for schleife um "durch" das Bild zu gehen
    for (int reihe = 0; reihe < width; reihe++)
    {
        for (int zeile = 0; zeile < height; zeile++)
        {
            // if pixel = black
            if (image[zeile][reihe].rgbtBlue == 0 &&
               image[zeile][reihe].rgbtGreen == 0 &&
               image[zeile][reihe].rgbtRed == 0)
               {
                    // change to custom color
                    image[zeile][reihe].rgbtBlue = 102;
                    image[zeile][reihe].rgbtGreen = 255;
                    image[zeile][reihe].rgbtRed = 255;
               }
        }
    }
}
