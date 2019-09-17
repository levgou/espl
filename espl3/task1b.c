#include <stdlib.h>

#include "task1b.h"

long get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    return fileSize;
}

node *gen_diff_list(FILE *org, FILE *new, long max_pos)
{
    node *list = NULL;
    long i;
    unsigned char org_char, new_char;
    char c_buf[1];

    for (i = 0; i < max_pos; i++)
    {
        fread(c_buf, 1, 1, org);
        org_char = (unsigned char)*c_buf;
        fread(c_buf, 1, 1, new);
        new_char = (unsigned char)*c_buf;

        if (org_char != new_char)
            list = list_append(list, diff_new(i, org_char, new_char));
    }

    return list;
}

node *gen_diff_list_from_files(char const *filePathOrg, char const *filePathNew)
{
    FILE *f_org = fopen(filePathOrg, "rb");
    FILE *f_new = fopen(filePathNew, "rb");

    long org_size = get_file_size(f_org);
    long new_size = get_file_size(f_new);
    long max_pos = (org_size < new_size) ? org_size : new_size;

    node *diff_list = gen_diff_list(f_org, f_new, max_pos);
    fclose(f_org);
    fclose(f_new);

    return diff_list;
}

void print_hex_diff(char const *filePathOrg, char const *filePathNew, FILE *output)
{
    node *diff_list = gen_diff_list_from_files(filePathOrg, filePathNew);

    list_print(diff_list, output);
    list_free(diff_list);
}

int get_list_len(node *list)
{
    int count = 0;
    while (list)
    {
        count++;
        list = list->next;
    }
    return count;
}

void print_list_len(node *diff_list, FILE *output)
{
    int count = get_list_len(diff_list);
    fprintf(output, "%d\n", count);
}

void print_hex_diff_num(char const *filePathOrg, char const *filePathNew, FILE *output)
{
    node *diff_list = gen_diff_list_from_files(filePathOrg, filePathNew);

    print_list_len(diff_list, output);
    list_free(diff_list);
}