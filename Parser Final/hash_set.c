#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_set.h"
#define MAX 1024


/* Initializes hash set, size is based on what user chooses */

hash_set* new_hash_set(int size)
{
    hash_set* set;
    int i;

    if (size < 1)
    {
        printf("set size must be larger than 0");;
        exit(0);
    }

    set = (hash_set*)malloc(sizeof(hash_set));
    set->element_count = 0;
    set->size = size;
    set->table = malloc(size * sizeof(char*));

    for(i = 0; i < size; i++ )
    {
            set->table[i] = NULL;
    }

    return set;
}

/* djb2 hash function, this is used to calculate unique indexes to insert and
to search.
*/

unsigned int hash_func(hash_set* set, char* str)
{
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % set->size;
}

/*Lookup function, this is used to find a key with set, this uses the
hash function to calculate the index of the string in question */

char* lookup(hash_set* set, char* str)
{
    unsigned int hash = hash_func(set, str);

    while(set->table[hash] != NULL)
    {
        if(strcmp(str,set->table[hash]) == 0)
        {
            return set->table[hash];
        }
        hash++;
    }
    return NULL;
}

/* insertion function, if the element is already present in a set,
the function does not insert */

int insert(hash_set* set, char* str)
{
    int unsigned hash = hash_func(set, str);

    if(set->element_count / set->size >= 0.8)
    {
        expand(set);
    }

    if(lookup(set, str) == NULL)
    {
        set->table[hash] = malloc(strlen(str) * sizeof(char*));
        strcpy(set->table[hash],str);
        set->element_count++;
        return 1;
    }
    return 0;
}

/* Memory allocation function, if the set reaches %80 capacity or more, its
bucket size is doubled to avoid collisions */

void expand(hash_set* set)
{
    int i;
    char** tmp;
    tmp = malloc(set->element_count * sizeof(char*));
    int hash;

    for(i = 0; i < set->element_count; i++)
    {
        if(set->table[i] != NULL)
        {
            tmp[i] = malloc(strlen(set->table[i]) * sizeof(char*));
            tmp[i] = set->table[i];
            set->table[i] = NULL;
        }
    }
    set->table = realloc(set->table, set->size * 2 * sizeof(char*));
    set->size = set->size * 2;

    for(i = 0; i < set->element_count; i++)
    {
        hash = hash_func(set,tmp[i]);
        set->table[hash] = tmp[i];
    }

    for(i = 0; i < set->element_count; i++)
    {
        free(tmp[i]);
    }
    free(tmp);
}

/*Deletion function, this is used for memory management purposes, this
deletes the entire hash */

void delete_set(hash_set* set)
{
    int i;
    for(i = 0; i < set->element_count; i++)
    {
        free(set->table[i]);
    }
    free(set->table);
    free(set);
}
