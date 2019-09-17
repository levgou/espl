#include <stdlib.h>

#include "task1a.h"

/* -------------------------------------------------  Diff ---------------------------------------------------------- */

diff *diff_new(long offset_, unsigned char orig_value_, unsigned char new_value_)
{
    diff *d = malloc(sizeof(diff));

    d->offset = offset_;
    d->orig_value = orig_value_;
    d->new_value = new_value_;

    return d;
}

void diff_del(diff *d)
{
    free(d);
}

/* -------------------------------------------------  Node ---------------------------------------------------------- */
node *node_new(diff *diff_data_, node *next_)
{
    node *n = malloc(sizeof(node));

    n->diff_data = diff_data_;
    n->next = next_;

    return n;
}

node *node_new_with_diff(node *next_, long offset_, unsigned char orig_value_, unsigned char new_value_)
{
    diff *d = diff_new(offset_, orig_value_, new_value_);
    node *n = node_new(d, next_);

    return n;
}

void node_del(node *n)
{
    free(n);
}

void node_del_recursive(node *n)
{
    diff_del(n->diff_data);
    node_del(n);
}

/* Print the nodes in diff_list in the following format: byte POSITION ORIG_VALUE NEW_VALUE. 
Each item followed by a newline character. */
char *PRINT_FORMAT = "byte %d %02X %02X\n";
void list_print_rec(node *diff_list, FILE *output)
{
    if (!diff_list)
        return;

    list_print_rec(diff_list->next, output);

    fprintf(output, PRINT_FORMAT,
            diff_list->diff_data->offset,
            diff_list->diff_data->orig_value,
            diff_list->diff_data->new_value);
}

void list_print(node *diff_list, FILE *output)
{
    list_print_rec(diff_list, output);
}

/* Add a new node with the given data to the list,
and return a pointer to the list (i.e., the first node in the list).
If the list is null - create a new entry and return a pointer to the entry.*/

node *list_append(node *diff_list, diff *data)
{
    return node_new(data, diff_list);
}

/* Free the memory allocated by and for the list. */
void list_free(node *diff_list)
{
    node *next = diff_list;
    while (diff_list)
    {
        next = diff_list->next;
        node_del_recursive(diff_list);
        diff_list = next;
    }
}
