#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // user input has to be between 1 & 8, both included
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // check if input procedure is correct
    // printf("stored: %i\n",height);

    // build pyramid
    int i, j, dots;
    // Zeilen
    for (i = 1; i <= height; i++)
    {
        dots = height - i;
        while (dots > 0)
        {
            printf(" ");
            dots--;
        }

        // Spalten
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}