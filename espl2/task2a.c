#include <stdio.h>

typedef int (*intToInt)(int);

int getMSB(int i);
int getLSB(int i);
int shiftRight(int i);
int shiftLeft(int i);

/* prints c to the standard output */
void echo_printer(char c)
{
    printf("%c", c);
}

/* convert a char to its ascii code and print it to the standard output*/
void ascii_printer(char c)
{
    printf("%d", c);
}

/* using a bit shifting function and a bit getter function - 
   print character in binary foramt */
void bin_print(char c, intToInt bitGetter, intToInt shifter)
{

    int cInt = (int)c;
    int i = 0;

    for (i = 0; i < 8; i++)
    {
        int b = (*bitGetter)(cInt);
        printf("%d", b);
        cInt = (*shifter)(cInt);
    }
}

/* convert a char to its ascii code in binary (least significant bit to the most 
significant representation) and print it to the standard output */
void binary_printer(char c)
{
    bin_print(c, getLSB, shiftRight);
}

/* convert a char to its ascii code in binary (most to least representation) 
   and print it to the standard output*/
void binary_printerML(char c)
{
    bin_print(c, getMSB, shiftLeft);
}