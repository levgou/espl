#include <stdio.h>
#include <string.h>

/* operates on 8 first bits */
int getMSB(int i)
{
    int mask = 128; /* 1000 0000 */
    return (i & mask) >> 7;
}

int getLSB(int i)
{
    return i & 1;
}

int shiftRight(int i)
{
    return i >> 1;
}

int shiftLeft(int i)
{
    return i << 1;
}

void charToBin(char c, char binRepr[], int (*bitGetter)(int), int (*shifter)(int))
{

    int cInt = (int)c;
    int i = 0;

    for (i = 0; i < 8; i++)
    {
        int b = (*bitGetter)(cInt);
        sprintf(&binRepr[i], "%d", b);
        cInt = (*shifter)(cInt);
    }
}