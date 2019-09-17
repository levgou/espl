#include "cmd_history.h"

#ifndef PROMPT_FLOW_UTILS
#define PROMPT_FLOW_UTILS

#define PROMPT_PATTERN  "[%s] >"
#define QUIT "quit\n"
#define ENDL "\n"
#define THILDA "~"

int execute(cmdLine *pCmdLine);
int change_dir(cmdLine *pCmdLine);
int show_history(CmdHistoryList *history_list);
int del_history_entry(cmdLine *cmd_line, CmdHistoryList *history_list);
int handle_history(cmdLine *cmd_line, CmdHistoryList *history_list);
char str_replace(char *string, char *pattern, char *replacement);
void addCmdToHistory(cmdLine *cmd_line, CmdHistoryList *history_list);
void build_history_str(CmdHistoryNode *node, char buf[]);
int handle_user_input(char user_input[], CmdHistoryList *history_list);

char is_user_defined_cmd(cmdLine *cmd_line);
int main_loop();
void addCmdToHistory(cmdLine *cmd_line, CmdHistoryList *history_list);
void handle_thilda_in_cmd(cmdLine *cmd_line);
void handle_exclamation_mark(cmdLine **p_cmd_line, CmdHistoryList *history_list);

int custom_exe(cmdLine *cmd_line, CmdHistoryList *history_list);
int execute(cmdLine *pCmdLine);

#endif