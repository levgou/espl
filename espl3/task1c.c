#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task1b.h"

void print_results_from_input(FILE *input, FILE *output)
{
    char *line = NULL;
    size_t len = 0;
    long i = 0;

    while (getline(&line, &len, input) != -1)
        i++;
    /* sscanf(line, "%s %s %d  %d", weekday, month, &day, &year); */
    fprintf(output, "%ld\n", i);
    free(line);
}

/*
int main(int argc, char const *argv[])
{

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
            output = fopen(argv[++i], "w");

        if (strcmp(argv[i], "-i") == 0)
            input = fopen(argv[++i], "r");

        else if (strcmp(argv[i], "-t") == 0)
            printer = print_hex_diff_num;

        else
        {
            files[file_index++] = argv[i];
        }
    }

    if (input)
    {
        print_results_from_input(input, output);
    }
    else
    {
        (*printer)(files[0], files[1], output);
    }

    if (output != stdout)
        fclose(output);

    if (input)
        fclose(input);

    return 0;
}
*/