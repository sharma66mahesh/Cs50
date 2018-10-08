/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define BUCKET_SIZE 6000


unsigned long int dictWords;

typedef struct node
{
    char word[LENGTH+1];    //+1 for '\0'
    struct node *next;
}node;


//define hash table. 200, an arbitrary number
node *table[BUCKET_SIZE];   
node *traverse;     //for traversing


/** Hash function Prototype **/
unsigned long int hash(unsigned char *str);


/**
 * Returns true if word is in dictionary else false.
 */
bool check(char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
