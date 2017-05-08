#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "hash_set.h"
#define MAX_LINE_SIZE 100

hash_set* file_list;

/* Files are extracted from the temporary file called includes.txt, after all
file names have been extracted they are placed into a hash set to avoid
repetitions */
hash_set* extract_files()
{
    char line[MAX_LINE_SIZE];
    file_list = new_hash_set(20);
    FILE* file;
    file = fopen("includes.txt","r");

    if (!file)
    {
        printf("File organizer could not open temporary file \n");
        exit(1);
    }

    while(fgets(line, sizeof(line)/sizeof(line[0]), file) != NULL)
    {
        if(line != "")
        {
            line[strcspn(line, "\n")]  = '\0';
            insert(file_list, line);
        }
    }
    fclose(file);
    return file_list;
}

/*Once the hash set has the necessary files, a temporary file with the content
of the include files (this includes any nested include files), will be
generated*/
void generate_temp_file()
{
    int i;
    char line[MAX_LINE_SIZE];
    FILE * file;
    FILE * spec_file;

    spec_file = fopen("include_specs.txt", "w");

    for(i = 0; i < file_list->size; i++)
    {
        if(file_list->table[i] != NULL)
        {
            file = fopen(file_list->table[i],"r");

            if(!file)
            {
                printf("Include file could not be opened");
                exit(1);
            }

            while(fgets(line, MAX_LINE_SIZE, file) != NULL)
            {
                fprintf(spec_file,"%s", line);
            }
        }
    }
    delete_set(file_list);
    fclose(spec_file);
}


/*In this function, all the temporary files that
were made will be opened, their data will be retrieved
and pasted into a single file which will be passed to the actual
scanner once it is created. The file should go by the name
program_name.prep.c. A regular expression is used to avoid
copying #define or #include directives into the new file */

int modify_file(char * source, char* file_name, int inc, int def)
{
    char line[MAX_LINE_SIZE];
    const char* define_regex = "#[ \t ]*define[ \t ]+([0-9]+|\"[a-zA-Z]+\")[ \t ]+([0-9]+|\"[a-zA-Z]+\")";
    const char* include_regex = "#[ \t ]*include[ \t ]+[\"][^ \t\n\"]+";
    regex_t define;
    regex_t include;
    int def_result;
    int inc_result;
    int def_counter = 0;
    FILE* file;
    FILE* inc_file;
    FILE* def_file;
    FILE* source_file;

    if(regcomp(&define,define_regex,REG_EXTENDED))
    {
        printf("Define regular expression could not be compiled\n");
        exit(1);
    }

    if(regcomp(&include,include_regex,REG_EXTENDED))
    {
        printf("Define regular expression could not be compiled\n");
        exit(1);
    }


    if(inc >= 1 || def >= 1)
    {
        file  = fopen(file_name, "w");

        if(inc >= 1)
        {
            inc_file = fopen("include_specs.txt","r");

            while(fgets(line, MAX_LINE_SIZE, inc_file))
            {
                inc_result = regexec(&include,line, 0, NULL, 0);
                def_result = regexec(&define,line, 0, NULL, 0);

                if(def_result == REG_NOMATCH && inc_result == REG_NOMATCH)
                {
                    fprintf(file, "%s",line);
                }
            }
            fclose(inc_file);
        }

        if(def >= 1)
        {
            def_file = fopen("defines_file.txt", "r");

            while(fgets(line, MAX_LINE_SIZE, def_file))
            {
                inc_result = regexec(&include,line, 0, NULL, 0);
                def_result = regexec(&define,line, 0, NULL, 0);

                if(def_result == REG_NOMATCH && inc_result == REG_NOMATCH)
                {
                    fprintf(file, "%s",line);
                }

                if(def_result != REG_NOMATCH)
                {
                    def_counter++;
                }
            }
            fclose(def_file);
        }
        else
        {
            source_file = fopen(source, "r");

            while(fgets(line, MAX_LINE_SIZE, source_file))
            {
                inc_result = regexec(&include,line, 0, NULL, 0);
                if(inc_result == REG_NOMATCH)
                {
                    fprintf(file, "%s",line);
                }
            }
            fclose(source_file);
        }
        fclose(file);
    }


    regfree(&include);
    regfree(&define);
    return def_counter;
}
