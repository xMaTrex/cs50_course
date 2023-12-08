#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // cla if user types in less or more than 2 commands
    // -> fehlermeldung
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }

    // make sure every input in argv[1] is a digit
    string cla = argv[1];
    for (int i = 0; cla[i] != '\0'; i++)
    {
        if (!isdigit(cla[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // cla from user = key
    int k = atoi(cla); // asci to int aus <stdlib.h>
    // printf("%i\n", k);

    string plaintext = get_string("plaintext:  ");
    // printf("%s\n", plaintext);
    printf("ciphertext: ");

    int len = strlen(plaintext);
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue; // verlasse die schleife
        }
        // char is alphabetical:

        // check if current char is upper
        int rotate;
        if (isupper(plaintext[i]))
        {
            rotate = 'A';
        }
        else
        {
            rotate = 'a';
        }

        // check distance from current char to 'a' or 'A'
        int p = plaintext[i] - rotate;

        // set char of ciphertext
        int c = (p + k) % 26;

        // print ciphered char
        printf("%c", c + rotate);
    }
    printf("\n");
    return 0;
}