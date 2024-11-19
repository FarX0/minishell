/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:56:14 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/19 16:03:32 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pipe handler for commands with pipes
void pipex(t_data *data, int i, int fd_in, int fd_out)
{
    int pipe_fd[2];
    pid_t pid;

    pipe(pipe_fd);

    pid = fork();
    if (pid == 0)
    {
        // First process
        if (fd_in != 0)
            dup2(fd_in, STDIN_FILENO);
        if (fd_out != 1)
            dup2(fd_out, STDOUT_FILENO);

        close(pipe_fd[0]);

        // Execute the command before the pipe
        execve_command(data);
    }
    else if (pid > 0)
    {
        // Parent process
        waitpid(pid, NULL, 0);
        close(pipe_fd[1]);
		//lofiorin po che ci fai con fd_in
        fd_in = pipe_fd[0];
    }
}
