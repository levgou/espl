#include <stdio.h>

extern int funcA(char *ch_p);

int main(int argc, char *argv[])
{
    int res;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: task0 arg1 \n");
        return 0;
    }

    char *arg1 = argv[1];

    res = funcA(arg1);
    printf("res %d\n", res);

    return 0;
}
