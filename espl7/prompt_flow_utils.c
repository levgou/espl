#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "LineParser.h"
#include "cmd_history.h"
#include "prompt_flow_utils.h"


int main_loop()
{
    char cwd_buf[PATH_MAX];
    char user_input[2048];
    CmdHistoryList *history_list = new_list();

    while (1)
    {
        getcwd(cwd_buf, PATH_MAX);
        printf(PROMPT_PATTERN, cwd_buf);
        fgets(user_input, 2048, stdin);

        if (strcmp(QUIT, user_input) == 0)
            break;
        else if (strcmp(ENDL, user_input) == 0)
            continue;

        handle_user_input(user_input, history_list);
    }

    free_list(history_list);
    printf("\n");
    return 0;
}

/* called by main loop for each user input */
int handle_user_input(char user_input[], CmdHistoryList *history_list)
{
    int ret;
    cmdLine *cmd_line = parseCmdLines(user_input);
    handle_thilda_in_cmd(cmd_line);
    handle_exclamation_mark(&cmd_line, history_list);

    if (is_user_defined_cmd(cmd_line))
        ret = custom_exe(cmd_line, history_list);
    else
        ret = execute(cmd_line);

    if(!ret)
        addCmdToHistory(cmd_line, history_list);
    /*
    freeCmdLines(cmd_line);
    */
    return ret;
}

void addCmdToHistory(cmdLine *cmd_line, CmdHistoryList *history_list)
{
    CmdHistoryNode *node = new_node(cmd_line);
    add_node(history_list, node);
}

void handle_thilda_in_cmd(cmdLine *cmd_line)
/* base assumption: thilda occurs max 1 time in an argument */
{
    char tmp[1024];
    char *home_dir = getenv("HOME");
    int i;

    for (i = 0; i < cmd_line->argCount; i++)
    {
        memset(tmp, '\0', strlen(tmp));
        char *cur_arg = cmd_line->arguments[i];
        strcpy(tmp, cur_arg);

        if (str_replace(tmp, THILDA, home_dir))
            replaceCmdArg(cmd_line, i, tmp);
    }
}

void handle_exclamation_mark(cmdLine **p_cmd_line, CmdHistoryList *history_list)
{
    if (strncmp((*p_cmd_line)->arguments[0], "!", 1) != 0)
        return;

    char buf[10];
    strcpy(buf, (*p_cmd_line)->arguments[0] + 1);
    long int cmd_num = strtol(buf, NULL, 10);

    if (cmd_num > history_list->size - 1)
    {
        fprintf(stderr, "Index is out of history list's bounds\n");
        return;
    }

    CmdHistoryNode *hist_cmd = history_list->tail;
    while (cmd_num--)
        hist_cmd = hist_cmd->prev;

    cmdLine *next_cmd = (*p_cmd_line)->next;
    free(*p_cmd_line);
    *p_cmd_line = hist_cmd->cmd;

    if (next_cmd)
        (*p_cmd_line)->next = next_cmd;
}

char *USER_CMDS[] = {"cd", "history"};
char USER_CMD_NUM = 2;
char is_user_defined_cmd(cmdLine *cmd_line)
{
    int i;
    for (i = 0; i < USER_CMD_NUM; i++)
    {
        if (strcmp(USER_CMDS[i], cmd_line->arguments[0]) == 0)
            return 1;
    }
    return 0;
}

/* -------------------------------------------------------
    Custom CMDs
------------------------------------------------------- */
int custom_exe(cmdLine *cmd_line, CmdHistoryList *history_list)
{
    int ret;
    char err_str[1024];

    if (strcmp("cd", cmd_line->arguments[0]) == 0)
        ret = change_dir(cmd_line);
    else if (strcmp("history", cmd_line->arguments[0]) == 0)
        ret = handle_history(cmd_line, history_list);

    if (ret)
    {
        perror(err_str);
        printf("%s\n", err_str);
    }

    return ret;
}

int handle_history(cmdLine *cmd_line, CmdHistoryList *history_list)
{
    if (cmd_line->argCount > 1 && !strcmp(cmd_line->arguments[1], "-d"))
        return del_history_entry(cmd_line, history_list);

    return show_history(history_list);
}

int del_history_entry(cmdLine *cmd_line, CmdHistoryList *history_list)
{
    long int idx_to_del = strtol(cmd_line->arguments[2], NULL, 10);
    if (idx_to_del > history_list->size - 1)
    {
        fprintf(stderr, "Index is out of history list's bounds\n");
        return 0;
    }
    CmdHistoryNode *rmed_node = del_node_at_index(history_list, idx_to_del);
    free_node(rmed_node);

    return 0;
}

int show_history(CmdHistoryList *history_list)
{
    int i = 0;
    char buf[1024];

    CmdHistoryNode *cur_node = history_list->tail;
    while (cur_node)
    {
        build_history_str(cur_node, buf);
        printf("%d. %s \n", i++, buf);
        cur_node = cur_node->prev;
    }
    return 0;
}

void build_history_str(CmdHistoryNode *node, char buf[])
{
    memset(buf, '\0', 1024);
    cmdLine *cur_cmd = node->cmd;

    int i;
    while(cur_cmd) {
        if(cur_cmd->idx != 0)
            strcat(buf, "| ");

        for (i = 0; i < cur_cmd->argCount; i++)
        {
            strcat(buf, cur_cmd->arguments[i]);
            strcat(buf, " ");
        }
        cur_cmd = cur_cmd->next;
    }
    
}

int change_dir(cmdLine *cmd_line)
{
    if (cmd_line->argCount == 1)
    {
        return chdir(getenv("HOME"));
    }
    else if (cmd_line->argCount == 2)
    {
        return chdir(cmd_line->arguments[1]);
    }
    return 1;
}

/* helpers */
char str_replace(char *string, char *pattern, char *replacement)
{
    char *p = strstr(string, pattern);
    if (!p)
        return 0;

    char buf[1024];
    memset(buf, '\0', strlen(buf));

    if (string == p) /* pattern was found @start of string */
    {
        strcpy(buf, replacement);
        strcat(buf, p + strlen(pattern));
    }
    else
    {
        strncpy(buf, string, strlen(string) - strlen(p));
        strcat(buf, replacement);
        strcat(buf, p + strlen(pattern));
    }

    memset(string, '\0', strlen(string));
    strcpy(string, buf);
    return 1;
}
