#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned int i;
    for(i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
    
    return 0;
}
