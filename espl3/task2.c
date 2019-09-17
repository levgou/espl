#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task1a.h"
#include "task1b.h"
#include "task1c.h"

#define MAXNUM 10
#define BASE 10

typedef void (*FileDiffPrinter)(char const *, char const *, FILE *);

char *INPUT_FORMAT = "byte %d %02X %02X\n";
node *gen_diff_list_from_input(FILE *input)
{
    char *line = NULL;
    size_t len = 0;
    node *head = NULL;

    unsigned char org_char = '\0';
    unsigned char new_char = '\0';
    int offset = 0;

    while (getline(&line, &len, input) != -1)
    {
        sscanf(line, INPUT_FORMAT, &offset, &org_char, &new_char);
        list_append(head, diff_new(offset, org_char, new_char));
    }
    return head;
}

/* ------------------------------------------------  Restore -------------------------------------------------------- */
int check_num_of_restores(char const *maybe_number)
{
    char *endptr;
    int number = strtol(maybe_number, &endptr, BASE);

    /* check if maybe_number is a pure number (no chars) */
    if (*endptr != '\0' || endptr == maybe_number)
        return 0;

    return number;
}

int compute_actual_restore_num(node *diff_list, int num_of_restores_arg)
{
    int list_len = get_list_len(diff_list);

    /* if 0 is passed restore all */
    if (!num_of_restores_arg)
        num_of_restores_arg = list_len;

    return list_len < num_of_restores_arg ? list_len : num_of_restores_arg;
}

void do_restore_recursive(FILE *f, int *num_of_restores_left, node *cur_node)
{
    if (!cur_node)
        return;

    do_restore_recursive(f, num_of_restores_left, cur_node->next);

    if (*num_of_restores_left)
    {
        *num_of_restores_left = *num_of_restores_left - 1;
        
        fseek(f, cur_node->diff_data->offset, SEEK_SET);
        fwrite(&cur_node->diff_data->orig_value, 1, 1, f);
    }
}

void do_restore(const char *new_file, int num_of_restores, node *diff_list)
{
    FILE *f = fopen(new_file, "rb+");
    do_restore_recursive(f, &num_of_restores, diff_list);
    fclose(f);
}

void restore_from_other_file(const char *org_file, const char *new_file, int num_of_restores_arg)
{
    node *diff_list = gen_diff_list_from_files(org_file, new_file);

    int actual_num_of_restores = compute_actual_restore_num(diff_list, num_of_restores_arg);
    do_restore(new_file, actual_num_of_restores, diff_list);

    list_free(diff_list);
}

void restore_from_results(const char *new_file, FILE *input, int num_of_restores_arg)
{
    node *diff_list = gen_diff_list_from_input(input);

    int actual_num_of_restores = compute_actual_restore_num(diff_list, num_of_restores_arg);
    do_restore(new_file, actual_num_of_restores, diff_list);

    list_free(diff_list);
}
/* ------------------------------------------------------------------------------------------------------------------ */

/* -------------------------------------------------  Setup --------------------------------------------------------- */
void setup_inout_file_pointers(FILE **input_p, FILE **output_p, int argc, char const *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
            *output_p = fopen(argv[++i], "w");

        else if (strcmp(argv[i], "-i") == 0)
            *input_p = fopen(argv[++i], "r");
    }
}

/* return 1 if restore mode is on otherwise 0 */
int setup_restore_params(int *num_of_restores, int argc, char const *argv[])
{
    int do_restore = 0;

    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            do_restore = 1;
            if (i < argc - 1)
                *num_of_restores = check_num_of_restores(argv[i + 1]);
            break;
        }
    }

    return do_restore;
}

FileDiffPrinter setup_printer(int argc, char const *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
            return print_hex_diff_num;

        else if (strcmp(argv[i], "-r") == 0)
            return NULL;
    }
    return print_hex_diff;
}

void setup_file_names(const char **org_file_p, const char **new_file_p, int argc, const char *argv[])
{
    const char *files[2];
    int file_index = 0;

    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-i") == 0)
            i++;
        else if (strcmp(argv[i], "-r") == 0 && check_num_of_restores(argv[i + 1]))
            i++;
        else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-r") == 0)
            continue;
        else
            files[file_index++] = argv[i];
    }

    files[file_index++] = argv[i];

    *org_file_p = files[0];
    *new_file_p = files[1];
}

/* ------------------------------------------------------------------------------------------------------------------ */

int main(int argc, char const *argv[])
{

    FILE *output = stdout;
    FILE *input = NULL;
    const char *org_file = NULL;
    const char *new_file = NULL;
    FileDiffPrinter printer = NULL;

    int do_restore = 0;
    int num_of_restores = 0;

    /* setup */
    setup_inout_file_pointers(&input, &output, argc, argv);
    setup_file_names(&org_file, &new_file, argc, argv);
    do_restore = setup_restore_params(&num_of_restores, argc, argv);
    printer = setup_printer(argc, argv);

    /* main flow */
    if (do_restore)
    {
        if (input)
            restore_from_results(new_file, input, num_of_restores);
        else
            restore_from_other_file(org_file, new_file, num_of_restores);
    }
    else
    {
        if (input)
            print_results_from_input(input, output);
        else
            (*printer)(org_file, new_file, output);
    }

    /* close files */
    if (output != stdout)
        fclose(output);

    if (input)
        fclose(input);

    return 0;
}
