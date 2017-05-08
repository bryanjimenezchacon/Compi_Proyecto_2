#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prep_scanner.h"
#include "file_organizer.h"
#include "parser.h"
#include "hash_set.h"
#define MAX_LINE_SIZE 100


void help(){
    printf(" <<-------------------------|| LAB COMPILER HELP ||------------------------->> \n\n");
    printf("                                           OPT         OPT         OPT\n");
    printf(" ./parser <Filename Source>  <Style> <Preprocessing> <Tabs> <Filename Result>  \n");
    printf("                              -GNU         -Y          -Y\n");
    printf("                              -BSD         -N          -N\n");
    printf("                              -LNX\n");
    printf("\n OPT * = Optional \n");
    printf("\n <<<<<<<<<<<<<<<<<<<<<<<<<    LAB COMPILER    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

char * appendix(char * string1, char * string2, char * string3, char * string4, char * string5)
{
    char * result = NULL;
    asprintf(&result, "%s%s%s%s%s", string1, string2, string3, string4, string5);
    return result;
}


int main(int argc, char * argv[])
{
    FILE * include_file;
    FILE * define_file;
    FILE * source_file;
    FILE * prep_file;
    FILE * error_file;
    int * line_numbers;
    int line_numbers_size;
    int def_lines;
    int inc;
    int def;
    int result;
    int i;
    char error_file_name[] = "errors.txt";
    char file[512];
    char new_file[512];
    char line[MAX_LINE_SIZE];
    char *tabsEnabled = "";
    char *IncludeEnabled = " original.c ";
    char *Init = "";
    char *End = "";
    char *Statement = "";
    char *name = (char *)malloc(1024);
    char *Fo = (char *)malloc(1024);
    char *Open = (char *)malloc(1024);

    if(argv[1] != NULL && strlen(argv[1]) <= sizeof(file)/sizeof(file[0])){

        if (strcmp(argv[1],"?") == 0) {
                help();
        
        } else {

            strcpy(file,argv[1]);
            strcpy(new_file, file);
            new_file[strlen(file)-1] = 0;
            strcat(new_file, "prep.c");
            source_file = fopen(file, "r");

            if(!source_file)
            {
                printf("\n  <<<<<<<<<<<<<<<<<< LAB COMPILER ERROR >>>>>>>>>>>>>>>>>>\n");
                printf("Source file could not be opened \n");
                exit(1);
            }
            prep_file = fopen(new_file, "w");

            if(!prep_file)
            {
                printf("\n  <<<<<<<<<<<<<<<<<< LAB COMPILER ERROR >>>>>>>>>>>>>>>>>>\n");
                printf("Copy of source file could not be opened \n");
                exit(1);
            }

            while(fgets(line, MAX_LINE_SIZE, source_file))
            {
                fprintf(prep_file,"%s",line);
            }
            fclose(source_file);
            fclose(prep_file);

            send_filename(new_file);
            prepin = fopen(new_file,"r+");
            insert_file();

            if(!prepin)
            {
                printf("\n  <<<<<<<<<<<<<<<<<< LAB COMPILER ERROR >>>>>>>>>>>>>>>>>>\n");
                printf("File could not be opened. \n");
                exit(0);
            }

            include_file = fopen("includes.txt", "w");
            fclose(include_file);
            define_file = fopen("defines_file.txt", "w");
            fclose(define_file);

            //preplex();

            fclose(prepin);
            preplex_destroy;
            inc = get_inc();
            def = get_def();
            free_filename();
            extract_files();
            generate_temp_file();
            modify_file(file, new_file, inc, def);
            error_file = fopen("errors.txt","w");
        	fclose(error_file);

    	    printf(" <<-----|| LAB COMPILER ||----->> \n\n");

            open_file(file);
            result = yyparse();
            close_file();

    	    ///------------------------------------------------
            ///>>>>>>>>>>>>>   STYLE SELECTION
            ///------------------------------------------------

            line_numbers = get_lines();
            line_numbers_size = get_error_count();

            if (argc < 7){
        	        
        	    if (line_numbers_size == 0){
        		
                    if (argc >= 4){

                        if(argv[3] != NULL && strcmp(argv[3],"-Y") == 0){
                            printf("  -     Include Activated      - \n");
                            strcat(name, "./pre ");
                            strcat(name, argv[1]);
                            system(name);
                            IncludeEnabled = " out.c ";

                        } else if (argv[3] != NULL && strcmp(argv[3],"-N") == 0){

                        } else if (argv[3] == NULL){
                            
                        }else{
                            help();
                            printf("Unknown argument %s, valid arguments (-Y, -N)\n", argv[3]);
                            exit(1);
                        }
                    }

                    
                    if (argc >= 5){

                        if(argv[4] != NULL && strcmp(argv[4],"-Y") == 0){
                            printf("  -       Tabs Activated     - \n");
                            tabsEnabled = " -i8 ";

                            if(argv[2] != NULL && strcmp(argv[2],"-GNU") == 0){
                                tabsEnabled = " -i8 -bli8 ";
                            }

                        } else if (argv[4] != NULL && strcmp(argv[4],"-N") == 0){
                            
                        }else{
                            help();
                            printf("Unknown argument %s, valid arguments (-Y, -N)\n", argv[4]);
                            exit(1);
                        }
                    }

                    
                    if (argc >= 6) {strcat(Fo, argv[5]);}

                    if(argv[2] != NULL && strcmp(argv[2],"-GNU") == 0)
                    
                    {
                        Init = "indent -kr -nbad -bap -nbc -bbo -bl -bli2 -bls -ncdb -nce -cp1 -cs -ndj -nfc1 -nfca -hnl -di2 -saf -sai -saw -nsc -sob -nip -lp -pcs -nprs";
                        
                        if (argc >= 6){ End = "-o "; }
                        else {End = "-o PPGNU.c";}

                        Statement = appendix(Init, tabsEnabled, IncludeEnabled, End, Fo);
                        
                        system(Statement);
                        printf("  - GNU PrettyPrint Generated - \n");
                        strcat(Open,"gedit ");
                        
                        if (argc >= 6){strcat(Open, Fo);}
                        else {strcat(Open, " PPGNU.c"); }

                        system(Open);
                    }

                    else if(argv[2] != NULL && strcmp(argv[2],"-BSD") == 0)
                    
                    {
                        Init = "indent -kr -sob -bap";
                        
                        if (argc >= 6){ End = "-o "; }
                        else {End = "-o PPBSD.c";}

                        Statement = appendix(Init, tabsEnabled, IncludeEnabled, End, Fo);
                        
                        system(Statement);
                        printf("  - BSD PrettyPrint Generated - \n");
                        strcat(Open,"gedit ");
                        
                        if (argc >= 6){strcat(Open, Fo);}
                        else {strcat(Open, " PPBSD.c"); }

                        system(Open);
                        
                    }


                    else if(argv[2] != NULL && strcmp(argv[2],"-LNX") == 0)
                    
                    {
                        Init = "indent -linux -bap";
                        
                        if (argc >= 6){ End = "-o "; }
                        else {End = "-o PPLNX.c";}

                        Statement = appendix(Init, tabsEnabled, IncludeEnabled, End, Fo);
                        
                        system(Statement);
                        printf("  - LNX PrettyPrint Generated - \n");
                        strcat(Open,"gedit ");
                        
                        if (argc >= 6){strcat(Open, Fo);}
                        else {strcat(Open, " PPLNX.c"); }

                        system(Open);
                
                    }

                    else 
                    
                    {
                        help();
                        printf("Unknown argument %s, valid arguments (-GNU, -BSD, -LNX)\n", argv[2]);
                        exit(1);
                    }

                    printf("\n <<<<<<    LAB COMPILER    >>>>>>\n");

                } else {

                    printf(" - Failed to generate the PrettyPrint -\n");
                    printf("\n  <<<<<< LAB COMPILER ERROR >>>>>>\n");

                }
            } 
             else {
                printf("The Function has too many parameters.\n\n");
                help();
            }
    	   
            remove("defines_file.txt");
            remove("includes.txt");
            remove("include_specs.txt");
            remove(new_file);
        }
    }
 
    else
 
    {
        printf("\n  <<<<<<<<<<<<<<<<<< LAB COMPILER ERROR >>>>>>>>>>>>>>>>>>\n");
        printf("  File not found or file name is too large\n");
        exit(1);
    }

    return 0;
}
