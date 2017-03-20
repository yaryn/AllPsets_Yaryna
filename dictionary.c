/**
 * Implements a dictionary's functionality.
 */
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

// the default dictionary are 143 091 words,all of which must be loaded into memory
#define HASHTABLE_SIZE 72000 //size hashtable (rows) 
// for [ ./speller texts/austinpowers.txt ] are ~ 73000 best :)

unsigned int words_all = 0;

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

char word[LENGTH + 1]; // this word is other word, not with node*.

node* hashtable[HASHTABLE_SIZE];

int hash(const char* word)
{
    int suma = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
        suma += tolower(word[i]); // for little letter

    return (suma % HASHTABLE_SIZE);
}
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // if the word exists, it can be found in the hash table
    // traversing linked lists (Перемещение связанных списков)
    
    // node *node1 = malloc(sizeof(node)); // was in video
    node* cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        unload();
        return false;
    }
    
    int word_check = hash(word);
    cursor = hashtable[word_check];
    while(cursor != NULL) 
    {
        // do somesing - для учета регистра i без
        // search in that linked list (about strcasecmp)
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error opened dictionary\n");
        return false;
    }
    // make a new word
    while (fscanf(file, "%s\n", word) != EOF)
    {
        // malloc a node * for each new word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // copy word into node
        strcpy(new_node->word, word);
        // node->word = "Hello";
        // strcpy(node->word, "Hello");

        int hashing_ind = hash(word);

        // if new belongs at head then prepend
        if (hashtable[hashing_ind] == NULL)
        {
            hashtable[hashing_ind] = new_node;
            new_node->next = NULL;
        }
        // if in middle or in end
        else
        {
            // insert into the linked list
            new_node->next = hashtable[hashing_ind];
            hashtable[hashing_ind] = new_node;
        }
        words_all++;
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words_all; // return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    int k = 0;
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = hashtable[i]; // = head;
        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
            // head = temp; ????  ->  ????
            return true;
        }
        // clean a hashtable
        hashtable[i] = NULL;
        k++;
    }
    if (k > 0)
        return true;
    else
        return false; // was false, no true
}