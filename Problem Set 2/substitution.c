#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Methods
void print_encrypted_message(string value, string key);

int main(int argc, string argv[])
{
    string error = "Usage: ./substitution key";

    if (argc != 2)
    {
        printf("%s\n", error);
        return 1;
    }

    string key = argv[1];

    int i = 0;
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

    if(i < 26)
    {
        printf("%s\n", "Key must contain 26 characters.");
        return 1;
    }

    print_encrypted_message(get_string("Input: "), key);
}

void print_encrypted_message(string value, string key)
{
    printf("ciphertext: ");

    int i = 0;
    while(value[i] != '\0')
    {
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
            printf("%c", value[i]);
        }

        i++;
    }

    printf("\n");
}