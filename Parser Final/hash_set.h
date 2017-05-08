#ifndef HASH_SET_H
#define HASH_SET_H


typedef struct hash_set
{
        int size;
        int element_count;
        char **table;

} hash_set;

hash_set* new_hash_set(int size);
void expand(hash_set* set);
int insert(hash_set* set, char* str);
char* lookup(hash_set* set, char* str);
unsigned int hash_func(hash_set* set, char* str);
void delete_set(hash_set* set);

#endif
