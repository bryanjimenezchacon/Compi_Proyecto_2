#include <stdio.h>
#include <stdlib.h>

#define STACK_LENGTH 128

static FILE *stack[STACK_LENGTH];
static int current = -1;

void stack_push(FILE *f)
{
	if (current < STACK_LENGTH - 1)
		stack[++current] = f;
	else {
		fprintf(stderr, "Stack overflow.");
		exit(1);
	}
}

char *stack_get_line(void)
{
	char *s = NULL;
	size_t n;
	if (current == -1)
		return NULL;
	if (getline(&s, &n, stack[current]) != -1)
		return s;
	else {
		current--;
		return stack_get_line();
	}
}
