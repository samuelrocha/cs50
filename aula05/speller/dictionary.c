// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Total Words
int amount_word = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // DONE
    int key;
    key = hash(word);

    for (node *tmp = table[key]; tmp != NULL; tmp = tmp->next)
    {
        if (!strcasecmp(word, tmp->word))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // DONE
    int key;
    key = (tolower(word[0]) - 'a') * 26;
    if (word[1] != '\0')
    {
        key += tolower(word[1]) - 'a';
    }
    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        amount_word++;
        int key = hash(word);
        node *tmp = malloc(sizeof(node));
        strcpy(tmp->word, word);
        tmp->next = table[key];
        table[key] = tmp;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // DONE
    return amount_word;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
