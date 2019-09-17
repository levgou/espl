#include <stdio.h>
int putUserInput(char buf[], unsigned int buf_size, unsigned int *n_chars_read)
{
    int c = 0, i = 0;

    while ((c = fgetc(stdin)) != '\n')
    {
        /* insufficient buffer space */
        if (i + 2 > buf_size)
        {
            printf("Insufficient buffer space!\n");
            return 1;
        }

        buf[i++] = (char)c;
    }

    /* add \0 to the string */
    buf[i] = 0;
    *n_chars_read = i;
    
    if (buf[0] == EOF)
        return -1;

    return 0;
}

void charToIntDec(char c, char decRepr[])
{
    int intC = (int)c;
    sprintf(&decRepr[0], "%d", intC);

    int numberOfDigits = 1;
    while ((intC /= 10) != 0)
        numberOfDigits ++;

    decRepr[numberOfDigits] = 0;
}