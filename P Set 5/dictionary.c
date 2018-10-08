/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include<malloc.h>
#include<string.h>


//our hash function
unsigned long int hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(char* word)
{
    // TODO
    
    //first lets find the bucket where the word is mapped by the hash table
    unsigned long index = hash((unsigned char*)word) % BUCKET_SIZE;
    int i = 0, matched = 0;
    char c;
    traverse = table[index];
    while(traverse != NULL)
    {
        //convert word to lowercase
        while((c = word[i++]) != '\0')
        {
            if((int)c >=65 && (int)c <= 90)
            {
                word[i-1] = (char)(c+32);
            }
        }
        
        if(strcmp(traverse->word,word) == 0)
        {
            matched++;
            printf("MATCHED%s & total match till now: %d\n", traverse->word, matched);
            return true;
        }
        traverse = traverse->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)   //arg is a dictionary file name
{
    // TODO
    //fill the table with null values
    for(int i = 0; i < BUCKET_SIZE; i++)
    {
        table[i] = NULL;
    }
    
    char temp[LENGTH+1];
    char c;
    int i = 0;
    unsigned long index;
    
    FILE *dict = fopen(dictionary, "r");

    if(dict != NULL)
    {
        //load all data from dictionary file into hash table.
        while((c = fgetc(dict)) != EOF)
        {
            if(c != '\n')
            {
                //it's a part of a word
                temp[i++] = c;
            }
            else
            {
                temp[i] = '\0';
                //we've loaded a word into temp
                
                index = hash((unsigned char*)temp) % BUCKET_SIZE;
                
                //store word into table at position index
                if(table[index] == NULL)
                {
                    table[index] = (node*)malloc(sizeof(node));
                    table[index]->next = NULL;
                    strcpy(table[index]->word, temp);
                    dictWords++;
                    
                }
                else
                {
                    //traverse table[index] until the end is reached
                    traverse = table[index];
                    while(traverse->next != NULL)
                        traverse = traverse->next;
                    node *newNode = (node*)malloc(sizeof(node));
                    
                    newNode->next = NULL;
                    strcpy(newNode->word, temp);
                    traverse->next = newNode;
                    dictWords++;
                }
                
                //restore i
                i = 0;                
            }
        }
        fclose(dict);
        return true;
    }
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dictWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i = 0; i < BUCKET_SIZE; i++)
    {
        traverse = table[i];
        while(traverse != NULL)
        {
            node* del = traverse;
            traverse = traverse->next;
            free(del);
        }
    }
    return true;
}
