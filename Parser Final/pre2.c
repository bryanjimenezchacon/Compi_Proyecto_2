#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * fpIn;
FILE * fpOut;
FILE * fin;
FILE * fout;
FILE * csis;
FILE * fOut;

void processDefine()
{
    
    fseek(fpOut, 0, SEEK_SET);
    char buffer[10000];
    char new[10000];
    int k = 0;
    while(!feof(fpOut))
    {
        buffer[k] = fgetc(fpOut);
        k++;
        
        
    }
    buffer[k - 1] = '\0';
    
  
    fseek(fout, 0, SEEK_SET);
    char token1[20][256];
    char token2[20][256];
    
    char * temp = buffer;
    
    int i = 0;
    while(!feof(fout))
    {
        
        fscanf(fout, "%s %[^\n]s\n", token1[i], token2[i]); // reads in token 1 and 2
        unsigned long length = strlen(token2[i]);
        if (token2[i][length - 1] == 13)
        {
            token2[i][length - 1] = '\0';
       }
        i++;
        
    }
    
    fclose(fpOut);
    
    int j = 0;
    int totalTokens = i;
    while (j < 3)
    {
    
        //int totalTokens = i;            // I changed this one
        i = 0;
    
        for (;i < totalTokens; i++)
        {
            char * track;                                       // creates a pointer to keep track of where token1 is
    
            track = strstr(buffer, token1[i]);                  // track is assigned to address of token1
            unsigned long length = strlen(token1[i]);           // gets length of token
    
            if (track != NULL)                                  // if track is assigned an address
            {
                int j = 0;
                for (;temp < track; temp++, j++)                // cycles until start of token1
                {
                    char put = *temp;
                    new[j] = put;                               // new buffer is filled till the start of token 1
            
                }
                new[j] = '\0';                                  // puts terminating character on
        
                unsigned long length2 = strlen(token2[i]);
                    
                    
                //printf("%s", token2[i]);
                
                
                strcat(new, token2[i]);                         // copies token 2 onto new string
        
                track += length;
                
        
                strcat(new, track);                             // copies string after token1 onto new string
        
                strcpy(buffer, new);                            // copies new string back to buffer string
        
        
                track = strstr(buffer, token1[i]);              // tests to see if there's another occurence of substring
        
                temp = buffer;
            
            
        // printf("%s", buffer);
        
            }
        }
        j++;
   }
    
    fOut = fopen("out.c", "w");
    
    //printf("%s\n", buffer);
    fprintf(fOut, "%s", buffer);                // THIS IS THE LINE
    
    
}




void parseFile()
{
    
    while(!feof(fpIn))
    {
        char buffer[256] = "";   // creates buffer to hold line read in
        fgets(buffer, 256, fpIn);   // gets line till end line
        
      
        char * track;       // pointer to buffer
        track = buffer;
        
        char * hPointer;    // pointer for value where #include is found

        char * dPointer = strstr(buffer, "#define");
        
        
        if (dPointer != NULL)
        {
            dPointer += 8;
            char c = *dPointer;
            while (c != '\0')
            {
                fprintf(fout, "%c", c);
                dPointer++;
                c = *dPointer;
            }
            continue;
        }
        
        
        hPointer = strstr(buffer, "#include");
        
        if (hPointer != NULL)
        {
            
            continue;
        }

        // printf("%s", buffer); dont use
        fprintf(fpOut, "%s", buffer);   
    }        
}





