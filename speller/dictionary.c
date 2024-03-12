// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void free_table(node *hash_table);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // compare input to words in the dictionary based on hash location for input word
    // get hash location
    unsigned int location = hash(word);

    // set dictionary word to first word in hash table
    node *temp = table[location];
    if (temp == NULL)
    {
        return false;
    }

    char *dictionary_word = temp->word;

    // store result of string comparison
    int result = strcasecmp(word, dictionary_word);
    // printf("comparing %s to %s\n", word, dictionary_word);

    // compare words
    while (result != 0)
    {
        // need to make a case for when word doesn't exist
        temp = temp->next;
        if (temp == NULL)
        {
            return false;
        }
        dictionary_word = temp->word;
        result = strcasecmp(word, dictionary_word);
        // printf("comparing %s to %s\n", word, dictionary_word);
    }

    // return true if a matching word was found
    if (result == 0)
    {
        return true;
    }

    // otherwise return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    word[0]
    word[1]
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the file
    FILE *dict_file = fopen(dictionary, "r");
    // if the file doesn't open return false
    if (dict_file == NULL)
    {
        printf("Could not open dictionary file\n");
        return false;
    }
    // printf("dictionary file opened\n");
    // copy dictionary contents into memory
    char new_word[LENGTH];
    while (fscanf(dict_file, "%s", new_word) != EOF)
    {
        // allocate memory for new node
        node *temp = malloc(sizeof(node));
        // copy the word into a new node
        for (int n = 0; n < LENGTH + 1; n++)
        {
            temp->word[n] = new_word[n];
        }
        // printf("loaded %s || %s\n", temp->word, new_word);
        int location = hash(new_word);
        // point temp node to start of hash table
        temp->next = table[location];
        // point hash table node to temp node
        table[location] = temp;
    }
    // printf("dictionary copied into memory\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // track number of words in dictionary
    unsigned int number_of_words = 0;

    // count number of nodes in hash table
    for (int i = 0; i < N; i++)
    {
        // if the next node in the table is not null, add to number count
        node *checker = table[i];
        while (checker != NULL)
        {
            number_of_words++;
            checker = checker->next;
        }
    }

    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate through the hash table
    for (int i = 0; i < N; i++)
    {
        node *last = table[i];
        free_table(last);
    }
    // printf("freed dictionary\n");
    return true;
}

void free_table(node *hash_table)
{
    // set last_node to the function input
    node *last_node = hash_table;

    if (last_node == NULL)
    {
        return;
    }
    // base case - if at the end of the line, free the last node
    if (last_node->next == NULL)
    {
        free(last_node);
    }
    // else move the function to the next node
    else
    {
        free_table(last_node->next);
    }
}