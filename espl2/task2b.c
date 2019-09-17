#include <stdio.h>

/* print a string using a print function passed as param */
void string_printer(char *array, void (*f)(char))
{
    while(*array) {
        (*f)(*array);
        printf(" ");
        array++;
    }
    printf("\n");
}
