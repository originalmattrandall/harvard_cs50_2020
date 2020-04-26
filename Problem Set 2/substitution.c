#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void print_encrypted_message(string value, string key);

int main(int argc, string argv[])
{
    string error = "Usage: ./substitution key";

    // a key must be passed to this program
    if (argc != 2)
    {
        printf("%s\n", error);
        return 1;
    }

    string key = argv[1];

    int i = 0;
    // iterate over every value in the key and run checks that it is valid
    while (key[i] != '\0')
    {
        if (!isalpha(key[i]))
        {
            printf("%s\n", error);
            return 1;
        }

        // Check for duplicate keys
        int j = i + 1;
        while (key[j] != '\0')
        {
            if (key[i] == key[j])
            {
                printf("%s\n", "Key must not contain repeat characters.");
                return 1;
            }

            j++;
        }

        i++;
    }

    // The key must match the same amount of characters in the english alphabet
    if (i < 26)
    {
        printf("%s\n", "Key must contain 26 characters.");
        return 1;
    }

    // Get the message to be encrypted from the user
    print_encrypted_message(get_string("Input: "), key);
}

/*
 * Function:  print_encrypted_message
 * --------------------
 * Given a specified key and value this function encrypts the value by
 *     changing the characters based on the key and printing the
 *     encrypted value.
 *
 * value: The string to encrypt
 *
 * key: the key used to encrypt the value of the value
 *
 */
void print_encrypted_message(string value, string key)
{
    printf("ciphertext: ");

    int i = 0;
    // Scan over every character in the value
    while (value[i] != '\0')
    {
        // Validate the character is lower case or upper case and process accordingly
        if (islower(value[i]))
        {
            int position = value[i] - 'a';

            printf("%c", tolower(key[position]));
        }
        else if (isupper(value[i]))
        {
            int position = value[i] - 'A';

            printf("%c", toupper(key[position]));
        }
        else
        {
            // Do not change the value if it is not an alphanumeric value
            printf("%c", value[i]);
        }

        i++;
    }

    printf("\n");
}
