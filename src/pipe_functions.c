#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>

void execute_pipe(t_data *data)
{
    int i = 0, pipe_fd[2], prev_fd = 0;
    pid_t pid;

    while (data->matrix_input[i] != NULL)
    {
        pipe(pipe_fd);
        pid = fork();
        if (pid == 0)  // Child process
        {
            if (prev_fd != 0)  // If not the first command, take input from the previous pipe
                dup2(prev_fd, 0);
            if (data->matrix_input[i + 1] != NULL)  // If not the last command, output to pipe
                dup2(pipe_fd[1], 1);
            close(pipe_fd[0]);
            char *args[] = {data->matrix_input[i], NULL};  // Command and arguments
            execve(data->matrix_input[i], args, data->env); // Execute the command
            exit(0);
        }
        else  // Parent process
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
            i++;
        }
    }

    while (wait(NULL) > 0);  // Wait for all child processes to finish
}
