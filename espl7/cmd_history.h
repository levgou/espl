#include "LineParser.h"

#ifndef HISTORY_SIZE
    #define HISTORY_SIZE 10
#endif

#ifndef CMD_HISTORY
#define CMD_HISTORY

typedef struct CmdHistoryNode
{
    struct CmdHistoryNode *next; /* next CmdHistory in chain */
    struct CmdHistoryNode *prev; /* prev CmdHistory in chain */
    struct cmdLine *cmd;
} CmdHistoryNode;

CmdHistoryNode *new_node(cmdLine *cmd);
CmdHistoryNode *free_node(CmdHistoryNode *history_node);

typedef struct CmdHistoryList
{
    int size;
    struct CmdHistoryNode *head;
    struct CmdHistoryNode *tail;
} CmdHistoryList;

CmdHistoryList *new_list(void);
void free_list(CmdHistoryList *history_list);
void add_node(CmdHistoryList *list, CmdHistoryNode *node);
CmdHistoryNode *del_node_at_index(CmdHistoryList *history_list, int idx_to_del);

#endif