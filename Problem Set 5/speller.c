// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Tracks total amount of words in dictionary file
int totalWords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);

    // Create a node and set it to the start of the index for navigating
    node* head = table[index];

    if(head != NULL)
    {
        node* currentPosition = head;

        // Use the nodes to move along the linked list and do a word comparison
        while(currentPosition != NULL)
        {
            if(strcasecmp(word, currentPosition->word) == 0)
            {
                // Word matches whats in the dictionary
                return true;
            }

            currentPosition = currentPosition->next;
        }
    }

    return false;
}

// Hashes word to a number
// Hash function used djb2 found at http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while((c = *word++))
        hash = ((hash << 5) + hash) + c;

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file in read mode and ensure its opened correctly.
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", dictionary);
    }

    char tempWord[LENGTH + 1];

    char word[45];

    // Loop through the dictinary file until a null char is found
    while (fscanf(file, "%s", word) != EOF)
    {
        // Alloc a node and memory for the word
        node* currentNode = malloc(sizeof(node));
        if (currentNode == NULL)
        {
            fclose(file);
            return false;
        }

        // Move word into the node
        strcpy(currentNode->word, word);
        int index = hash(word);

        currentNode->next = table[index];
        table[index] = currentNode;
        totalWords++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Check for nodes and clear them out of the table
    for (int i = 0; i < N; i++)
    {
        node* currentNode = table[i];
        while(currentNode != NULL)
        {
            // Store the currentNode
            node* tempNode = currentNode;

            // Set position at the next node
            currentNode = currentNode->next;

            // Free the node used the stored temp
            free(tempNode);
        }
    }

    return true;
}
