#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "LineParser.h"
#include "prompt_flow_utils.h"
#include "task2a.h"

void hook_io(cmdLine *cmd_line, char io_need_close[], int **pipes);
void close_files(char io_need_close[]);
int calc_pipeline_len(cmdLine *cmd_line);
int execute_cmd(cmdLine *pCmdLine, int **pipes);

int main(int argc, char const *argv[])
{
    return main_loop();
}

int execute(cmdLine *pCmdLine)
{
    int exit_code;
    int exit_code_acc = 0;
    int pid;
    cmdLine *cur_cmd = pCmdLine;

    int num_cmds_in_pipe_line = calc_pipeline_len(pCmdLine);
    int **pipes = createPipes(num_cmds_in_pipe_line - 1);
    int *pids = (int *)malloc(sizeof(int) * (num_cmds_in_pipe_line + 1));
    int pids_count = 0;
    char is_blocking = 0;

    int i;
    for (i = 0; i < num_cmds_in_pipe_line; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            break;
        }

        if (pid == 0)
        {
            exit_code = execute_cmd(cur_cmd, pipes);
            _exit(exit_code);
        }

        if(cur_cmd->next)
            close(pipes[i][1]);
        if(cur_cmd->idx)
            close(pipes[i - 1][0]);

        /* printf("ps: %s , pid: %d\n", cur_cmd->arguments[0], pid); */
        pids[pids_count++] = pid;
        is_blocking |= cur_cmd->blocking;
        cur_cmd = cur_cmd->next;
    }
    pids[pids_count] = 0;

    if (is_blocking)
    {
        for( i = 0; i < pids_count; i++)
        {
            /* printf("waiting for: %d\n", pids[i]); */
            waitpid(pids[i], &exit_code, 0);
            /* printf("finished waiting for: %d\n", pids[i]); */
            exit_code_acc += exit_code;
        }
    }
    releasePipes(pipes, num_cmds_in_pipe_line - 1);

    free(pids);

    return exit_code_acc;
}

int execute_cmd(cmdLine *pCmdLine, int **pipes)
{
    int exit_code;
    char err_str[1024];
    char io_need_close[2] = {0, 0};

    hook_io(pCmdLine, io_need_close, pipes);
    /* fprintf(stderr, "Run %s %s\n ", pCmdLine->arguments[0], pCmdLine->arguments[1]); */
    exit_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
    /* printf("ps: %s , finished\n", pCmdLine->arguments[0]); */

    if (exit_code)
    {
        perror(err_str);
        printf("%s", err_str);
    }

    close_files(io_need_close);

    return exit_code;
}

void hook_io(cmdLine *cmd_line, char io_need_close[], int **pipes)
{
    int *left_pipe, *right_pipe;

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

    if ((left_pipe = leftPipe(pipes, cmd_line)))
    {
        /* fprintf(stderr, "connect %s STDIN from %d\n", cmd_line->arguments[0], left_pipe[0]); */
        close(STDIN_FILENO);
        dup2(left_pipe[0], STDIN_FILENO);
        close(left_pipe[0]);
    }

    if ((right_pipe = rightPipe(pipes, cmd_line)))
    {
        /* fprintf(stderr, "connect %s STDOU to %d\n", cmd_line->arguments[0], right_pipe[0]); */
        close(STDOUT_FILENO);
        dup2(right_pipe[1], STDOUT_FILENO);
        close(right_pipe[1]);
    }
}

void close_files(char io_need_close[])
{
    if (io_need_close[0])
        close(STDIN_FILENO);

    if (io_need_close[1])
        close(STDOUT_FILENO);
}

int calc_pipeline_len(cmdLine *cmd_line)
{
    int count = 0;
    while (cmd_line)
    {
        count++;
        cmd_line = cmd_line->next;
    }
    return count;
}
