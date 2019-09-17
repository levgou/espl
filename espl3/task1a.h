#ifndef TASK1_A
#define TASK1_A

#include <stdio.h>

/* -------------------------------------------------  Diff ---------------------------------------------------------- */
typedef struct diff
{
    long offset;              /* offset of the difference in file starting from zero*/
    unsigned char orig_value; /* value of the byte in ORIG */
    unsigned char new_value;  /* value of the byte in NEW */
} diff;

diff *diff_new(long offset_, unsigned char orig_value_, unsigned char new_value_);
void diff_del(diff *d);

/* -------------------------------------------------  Node ---------------------------------------------------------- */
typedef struct node node;
struct node
{
    diff *diff_data; /* pointer to a struct containing the offset
                        and the value of the bytes in each of the files*/
    node *next;
};

node *node_new(diff *diff_data_, node *next_);
node *node_new_with_diff(node *next_, long offset_, unsigned char orig_value_, unsigned char new_value_);

void node_del(node *n);
void node_del_recursive(node *n);

void list_print(node *diff_list, FILE *output);
node *list_append(node *diff_list, diff *data);
void list_free(node *diff_list);

#endif