#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pipefd[2];
    int second_pipefd[2];
    
    int childpid1, childpid2, childpid3;
    
    int exit_code1, exit_code2;
    char *cmd[3] = {"ls", NULL, NULL};
    char *cmd2[3] = {"grep", ".c", NULL};
    char *cmd3[3] = {"wc", NULL, NULL};
    
    pipe(pipefd);
    pipe(second_pipefd);

    childpid1 = fork();
    if (childpid1 == 0)
    {
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp("ls", cmd);

        _exit(0);
    }
    close(pipefd[1]);

    /* if not closing this end there is a dead-lock when awaiting child */
    childpid2 = fork();
    if (childpid2 == 0)
    {
        close(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        close(STDOUT_FILENO);
        dup2(second_pipefd[1], STDOUT_FILENO);
        close(second_pipefd[1]);

        execvp("grep", cmd2);

        _exit(0);
    }
    /* if not closing this end there is a dead-lock when awaiting child */
    close(pipefd[0]);
    close(second_pipefd[1]);

    childpid3 = fork();
    if (childpid3 == 0)
    {
        close(STDIN_FILENO);
        dup2(second_pipefd[0], STDIN_FILENO);
        close(second_pipefd[0]);
        execvp("wc", cmd3);

        _exit(0);
    }
    close(second_pipefd[0]);

    /* If not waiting and closing pipe - the procs wont exit but 
    the main proc will continue  */
    waitpid(childpid1, &exit_code1, 0);
    waitpid(childpid2, &exit_code2, 0);
    waitpid(childpid3, &exit_code2, 0);

    return 0;
}
