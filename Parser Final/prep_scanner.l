
/* Description: C preprocessor scanner */

%option yylineno
%option header-file="prep_scanner.h"
%option outfile="prep_scanner.c"
%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "strrep.h"
#define MAX_LINE_SIZE 100
#define MAX 10
YY_BUFFER_STATE file_stack[MAX];
int stack_counter = 0;
int inc = 0;
int def = 0;
int def_counter = 0;
char* file_name;
FILE * file;
%}

%s INCLUDE_FILE
%s DEFINE_MACRO
%s COMMENT

%%
#[ \t ]*include[ \t ]*[\"] BEGIN (INCLUDE_FILE);
<INCLUDE_FILE>[^ \t\n\"]+ {
    inc = 1;
    if(stack_counter >= MAX)
    {
        printf("Includes are nested too deeply \n");
        exit(1);
    }

    file_stack[stack_counter++] = YY_CURRENT_BUFFER;

    prepin = fopen(preptext, "r");
    file = fopen("includes.txt","a+");

    if(!file)
    {
        printf("Includes temporary file could not be opened");
        exit(1);
    }

    fprintf(file,"%s\n", preptext);
    fclose(file);

    if(! prepin)
    {
        printf("Header file could not be opened \n");
        exit(1);
    }
    prep_switch_to_buffer(
        prep_create_buffer( prepin, YY_BUF_SIZE));

    BEGIN(INITIAL);
}

#[ \t ]*define[ \t ]+ BEGIN(DEFINE_MACRO);
<DEFINE_MACRO>[a-zA-Z_]+[0-9]*[ \t ]+([0-9]+|\"[a-zA-Z]+\") {
    def = 1;
    if(stack_counter == 1)
    {
        char line[MAX_LINE_SIZE];
        char buffer[1024];
        char copy[100];
        char id[100];
        char value[100];
        char delimiter[] = " \r\n";
        FILE* file;
        FILE* new_file;

        strcpy(copy,preptext);
        strcpy(id,strtok(copy, delimiter));
        strcpy(value,strtok(NULL, delimiter));

        file = fopen(file_name,"r");
        new_file = fopen("defines_file.txt","a+");

        while(fgets(line, MAX_LINE_SIZE, file) != NULL)
        {
            strcpy(buffer,repl_str(line, id, value));
            fprintf(new_file, "%s", buffer);
        }
        fclose(file);
        fclose(new_file);
    }
    BEGIN(INITIAL);
}

<<EOF>> {
          if(--stack_counter == 0)
          {
              yyterminate();
          }
          else
          {
              prep_delete_buffer(YY_CURRENT_BUFFER);
              prep_switch_to_buffer(file_stack[stack_counter]);
          }
      }
"/*" BEGIN(COMMENT);

<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>[^*\n]+
<COMMENT>"*"
<COMMENT>\n preplineno++;
"//"[^\n]*
.
%%

void insert_file()
{
    file_stack[stack_counter++] == YY_CURRENT_BUFFER;
}

void send_filename(char* name)
{
    file_name = malloc(sizeof(name)/sizeof(name[0]) * sizeof(char*));
    strcpy(file_name, name);
}

void free_filename()
{
    free(file_name);
}

int get_inc()
{
    return inc;
}

int get_def()
{
    return def;
}

int get_def_count()
{
    return def_counter;
}
