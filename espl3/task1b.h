#include "task1a.h"
#include <stdio.h>

#ifndef TASK1_B
#define TASK1_B

void print_list_len(node *diff_list, FILE *output);
int get_list_len(node *list);
node *gen_diff_list_from_files(char const *filePathOrg, char const *filePathNew);
void print_hex_diff(char const *filePathOrg, char const *filePathNew, FILE *output);
void print_hex_diff_num(char const *filePathOrg, char const *filePathNew, FILE *output);

#endif