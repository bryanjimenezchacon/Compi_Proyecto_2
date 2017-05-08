gg = G

CC = gcc

all: primero segundo compiler 

primero:
	$(CC) maining.c filestack.c pre.c pre2.c -o pre

segundo:
	$(CC) -g maining.c filestack.c pre.c pre2.c -o pre

compiler:
	flex --prefix=prep prep_scanner.l
	bison --defines=parser.h --output=parser.c parser.y
	flex scanner.l
	gcc -g -o parser main.c hash_set.c prep_scanner.c file_organizer.c strrep.c scanner.c parser.c -lfl


clean:
	rm -rf *o compiler
