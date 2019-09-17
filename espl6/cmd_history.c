#include <stdlib.h>

#include "LineParser.h"
#include "cmd_history.h"

#ifndef NULL
#define NULL 0
#endif

CmdHistoryList *new_list(void)
{
    CmdHistoryList *p_history_list = (CmdHistoryList *)malloc(sizeof(CmdHistoryList));
    p_history_list->head = NULL;
    p_history_list->tail = NULL;

    p_history_list->size = 0;
    return p_history_list;
}

void free_list(CmdHistoryList *history_list)
{
    CmdHistoryNode *cur_node = history_list->head;
    while (cur_node)
        cur_node = free_node(cur_node);

    free(history_list);
}

void add_node(CmdHistoryList *list, CmdHistoryNode *node)
{
    node->next = list->head;
    if (node->next)
        node->next->prev = node;

    node->prev = NULL;
    list->head = node;

    if (!list->tail)
        list->tail = node;

    if (list->size < HISTORY_SIZE)
    {
        list->size++;
    }
    else
    {
        /* size == HISTORY_SIZE  - remove - tail */
        list->tail = list->tail->prev;
        free_node(list->tail->next);
        list->tail->next = NULL;
    }
}

CmdHistoryNode *del_node_at_index(CmdHistoryList *history_list, int idx_to_del)
{
    CmdHistoryNode *cur_node = history_list->tail;
    while (idx_to_del--)
        cur_node = cur_node->prev;

    if (cur_node == history_list->tail)
    {
        cur_node->prev->next = NULL;
        history_list->tail = cur_node->prev;
    }
    else if (cur_node == history_list->head)
    {
        history_list->head = cur_node->next;
        history_list->head->prev = NULL;
    }
    else /* node is in the middle of the list */
    {
        cur_node->prev->next = cur_node->next;
        cur_node->next->prev = cur_node->prev;
    }
    history_list->size--;

    cur_node->next = NULL;
    cur_node->prev = NULL;
    return cur_node;
}

CmdHistoryNode *new_node(cmdLine *cmd)
{
    CmdHistoryNode *p_history_node = (CmdHistoryNode *)malloc(sizeof(CmdHistoryNode));
    p_history_node->next = NULL;
    p_history_node->prev = NULL;
    p_history_node->cmd = copy_cmd_line(cmd);

    return p_history_node;
}

CmdHistoryNode *free_node(CmdHistoryNode *history_node)
{
    CmdHistoryNode *next_node = history_node->next;
    freeCmdLines(history_node->cmd);
    free(history_node);
    return next_node;
}
