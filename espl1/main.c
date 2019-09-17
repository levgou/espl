#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* task 1a */
int putUserInput(char buf[], unsigned int buf_size, unsigned int *n_chars_read);
void charToIntDec(char c, char decRepr[]);

/* task 1b */
void charToBinFromLSB(char c, char binRepr[]);

/* task 1c */
void charToBinFromMSB(char c, char binRepr[]);

int main(int argc, char const *argv[])
{
    char userInput[10];
    unsigned int userInputSize = 10;
    unsigned int num_chars_from_user = -1;

    unsigned int i;
    char buf[9];

    FILE *output = stdout;
    void (*charFormatter)(char, char[]) = charToIntDec;

    /* setup */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
            output = fopen(argv[++i], "w");

        else if (strcmp(argv[i], "-l") == 0)
            charFormatter = charToBinFromLSB;
        
        else if (strcmp(argv[i], "-b") == 0)
            charFormatter = charToBinFromMSB;
        
        else
        {
            printf("invalid parameter - %s\n", argv[i]);
            return 1;
        }
    }

    /* -1 will return if user inputs EOF */
    while (putUserInput(userInput, userInputSize, &num_chars_from_user) != -1)
    {
        for (i = 0; i < num_chars_from_user; i++)
        {
            (*charFormatter)(userInput[i], buf);
            fprintf(output, "%s", buf);

            if (i != num_chars_from_user -1) 
                fprintf(output, " ");
        }
        fprintf(output, "\n");
    }

    return 0;
}
