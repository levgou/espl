#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/limits.h>

#include "cmd_history.h"
#include "prompt_flow_utils.h"

void hook_io(cmdLine *cmd_line, char io_need_close[]) ;
void close_files(char io_need_close[]);

int main(int argc, char const *argv[])
{
    return main_loop();
}

int execute(cmdLine *pCmdLine)
{
    char err_str[1024];
    int exit_code;
    int pid = fork();
    char io_need_close[2] = {0, 0};

    if (pid == -1)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        hook_io(pCmdLine, io_need_close);
        exit_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        if (exit_code)
        {
            perror(err_str);
            printf("%s", err_str);
        }
        close_files(io_need_close);
        _exit(exit_code);
    }

    if (pCmdLine->blocking)
        waitpid(pid, &exit_code, 0);

    return exit_code;
}

void hook_io(cmdLine *cmd_line, char io_need_close[]) 
{
    if (cmd_line->outputRedirect)
    {
        close(STDOUT_FILENO);
        dup2(open(cmd_line->outputRedirect, O_WRONLY | O_CREAT, 0666), STDOUT_FILENO);
        io_need_close[1] = 1;
    }

    if (cmd_line->inputRedirect)
    {
        close(STDIN_FILENO);
        dup2(open(cmd_line->inputRedirect, O_RDONLY), STDIN_FILENO);
        io_need_close[0] = 1;
    }
}

void close_files(char io_need_close[])
{
    if (io_need_close[0])
        close(STDIN_FILENO);
    
    if (io_need_close[1])
        close(STDOUT_FILENO);

}
