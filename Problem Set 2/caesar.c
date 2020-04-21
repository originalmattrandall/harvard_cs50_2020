#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Methods
void PrintCipherText(string userInputWord, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string argument = argv[1];

    int i = 0;
    while (argument[i] != '\0')
    {
        if (isalpha(argument[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        i++;
    }

    int key = atoi(argv[1]);

    PrintCipherText(get_string("plaintext: "), key);
}

// *
// * Description: Iterates over a word and moves the original char by a user set position
// *
// * Result: Prints the final result of the rotated word
// *
void PrintCipherText(string userInputWord, int key)
{
    printf("ciphertext: ");

    int i = 0;
    while (userInputWord[i] != '\0')
    {
        if (islower(userInputWord[i]))
        {
            printf("%c", (((userInputWord[i] + key) - 97) % 26) + 97);
        }
        else if (isupper(userInputWord[i]))
        {
            printf("%c", (((userInputWord[i] + key) - 65) % 26) + 65);
        }
        else
        {
            printf("%c", userInputWord[i]);
        }


        i++;
    }

    printf("\n");
}