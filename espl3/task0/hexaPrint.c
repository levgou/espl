#include <stdio.h>
#include <stdlib.h>

void printHex(char *buf, size_t buf_s)
{
    int i;
    for (i = 0; i < buf_s; i++)
        printf("%02X ", (unsigned char)buf[i]);

    printf("\n");
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    char const *filePath = argv[1];

    FILE *f = fopen(filePath, "rb");
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fileSize + 1);
    fread(string, fileSize, 1, f);
    fclose(f);
    string[fileSize] = 0;

    printHex(string, fileSize);

    string = NULL;
    free(string);

    return 0;
}
