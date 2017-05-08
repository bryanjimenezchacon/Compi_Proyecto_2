#ifndef FILE_ORGANIZER_H
#define FILE_ORGANIZER_H
#include "hash_set.h"

hash_set* extract_files();
void generate_temp_file();
int modify_file(char * source, char* file_name, int inc, int def);


#endif
