#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "LineParser.h"

int execute(cmdLine *pCmdLine);
int handle_user_input(char user_input[]);
char is_user_defined_cmd(cmdLine *cmd_line);
int custom_exe(cmdLine *cmd_line);
int change_dir(cmdLine *pCmdLine);
void handle_thilda_in_cmd(cmdLine *cmd_line);
char str_replace(char *string, char *pattern, char *replacement);

char *PROMPT_PATTERN = "[%s] >";
char *QUIT = "quit\n";
char *ENDL = "\n";
char *THILDA = "~";
int main_loop()
{
    char cwd_buf[PATH_MAX];
    char user_input[2048];

    while (1)
    {
        getcwd(cwd_buf, PATH_MAX);
        printf(PROMPT_PATTERN, cwd_buf);
        fgets(user_input, 2048, stdin);

        if (strcmp(QUIT, user_input) == 0)
            break;
        else if (strcmp(ENDL, user_input) == 0)
            continue;

        handle_user_input(user_input);
    }

    printf("\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    main_loop();
    return 0;
}

int handle_user_input(char user_input[])
{
    int ret;
    cmdLine *cmd_line = parseCmdLines(user_input);
    handle_thilda_in_cmd(cmd_line);

    if (is_user_defined_cmd(cmd_line))
        ret = custom_exe(cmd_line);
    else
        ret = execute(cmd_line);

    freeCmdLines(cmd_line);
    return ret;
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
        
        if(str_replace(tmp, THILDA, home_dir))
            replaceCmdArg(cmd_line, i, tmp);
    }
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

int execute(cmdLine *pCmdLine)
{
    char err_str[1024];
    int exit_code;
    int pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        exit_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        if (exit_code)
        {
            perror(err_str);
            printf("%s", err_str);
        }
        _exit(exit_code);
    }
    else
    {
        if (pCmdLine->blocking)
            waitpid(pid, &exit_code, 0);
    }

    return exit_code;
}

int custom_exe(cmdLine *cmd_line)
{
    int ret;
    char err_str[1024];

    if (strcmp("cd", cmd_line->arguments[0]) == 0)
        ret = change_dir(cmd_line);

    if (ret)
    {
        perror(err_str);
        printf("%s\n", err_str);
    }

    return 1;
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