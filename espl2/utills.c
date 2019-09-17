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
