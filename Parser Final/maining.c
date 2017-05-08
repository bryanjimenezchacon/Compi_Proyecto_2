#include <stdio.h>

void stage1(FILE *, FILE *);
void stage2(FILE *, FILE *);
void stage3(FILE *, FILE *);

void readHeader(char input[]);
void parseFile();
void processDefine();

FILE * fpIn;
FILE * fpOut;
FILE * fin;
FILE * fout;
FILE * csis;
FILE * fOut;

int main(int argc, char * argv[])
{
	FILE *i, *o;
	
	if(argv[1] != NULL)    	
	{

		i = fopen(argv[1], "r");
		o = fopen("output1.c", "w");
		stage1(i, o);
		fclose(i);
		fclose(o);

		i = fopen("output1.c", "r");
		o = fopen("output2.c", "w");
		stage2(i, o);
		fclose(i);
		fclose(o);

		i = fopen("output2.c", "r");
		o = fopen("output.c", "w");
		stage3(i, o);
		fclose(i);
		fclose(o);
	
		remove("output1.c");
		remove("output2.c");
	

		//TWOOO
		
		char input[256];
	    
	    if (!(fpIn = fopen("output.c", "r")))
	    {
			printf("Can't open test.c\n");
	    }
	    
	    fout = fopen("define.txt", "w+");
	    fpOut = fopen("out.c","w+");
	
	    parseFile();
	    processDefine();
		remove("output.c");    
	
	}
	   else
    {
        printf("File not found or file name is too large");
        exit(1);
    }

    	return 0;

}
