#include <stdio.h>

#define MAX_CHARS 10

void binary_printer(char c);

/* reads a string from standard input and saves it to s 
   assumption - user input is <= 10 chars */
void string_reader(char *s)
{
    if (fgets(s, MAX_CHARS + 1, stdin) == NULL)
        sprintf(s, "%d", -1);
    
    /* replace \n with \0 */
    while(*s != '\n') s++;
    *s = 0;
}

/* receives a string and performs a bitwise or on the ascii code of all of its chars, 
   and then prints the result in binary */
void bitwise_or(char *s)
{

    char res = 0;
    while (*s) {
        res |= *s;
        s++;
    }

    binary_printer(res);
    printf("\n");
}
