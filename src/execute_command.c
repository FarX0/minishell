/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lofiorin <lofiorin@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/18 02:25:53 by lofiorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>


void execute_command(t_data *data)
{
    int i = 0;
    int fd_in = 0;
    int fd_out = 1;
    
    while (data->matrix_input[i] != NULL)
    {
        if (ft_strcmp(data->matrix_input[i], "|") == 0)
        {
            pipex(data, i, fd_in, fd_out);
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], ">") == 0)
        {
            handle_redirection(data, i, '>');
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], "<") == 0)
        {
            handle_redirection(data, i, '<');
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], ">>") == 0)
        {
            handle_redirection(data, i, '>');
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], "<<") == 0)
        {
            handle_here_doc(data, i);
            break;
        }
        else
        {
            // Normal command execution
            execute_normal_command(data);
            break;
        }
        i++;
    }
}

// Handle normal command execution
void execute_normal_command(t_data *data)
{
    if (ft_strcmp("echo", data->matrix_input[0]) == 0)
        builtin_echo(data);
    else if (ft_strcmp("cd", data->matrix_input[0]) == 0)
        builtin_cd(data);
    else if (ft_strcmp("pwd", data->matrix_input[0]) == 0)
        builtin_pwd();
    else if (ft_strcmp("export", data->matrix_input[0]) == 0)
        builtin_export(data);
    else if (ft_strcmp("unset", data->matrix_input[0]) == 0)
        builtin_unset(data);
    else if (ft_strcmp("env", data->matrix_input[0]) == 0)
        builtin_env(data);
    else
        execve_command(data);
}

// Handle the redirections: >, <, >>, <<
void handle_redirection(t_data *data, int i, char redir)
{
    int fd;
    
    if (redir == '>' || redir == '>>')
    {
        if (redir == '>')
            fd = open(data->matrix_input[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd = open(data->matrix_input[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (fd == -1)
        {
            perror("minishell: open");
            return;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (redir == '<')
    {
        fd = open(data->matrix_input[i + 1], O_RDONLY);

        if (fd == -1)
        {
            perror("minishell: open");
            return;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (redir == '>')
    {
        handle_here_doc(data, i);
    }
}

// Handle here-doc redirection (<<)
void handle_here_doc(t_data *data, int i)
{
    char *line;
    int fd;

    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("minishell: open");
        return;
    }

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, data->matrix_input[i + 1]) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);

    fd = open(".heredoc_tmp", O_RDONLY);
    if (fd == -1)
    {
        perror("minishell: open");
        return;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
}

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
        fd_in = pipe_fd[0];
    }
}

// Execute the command using execve
void execve_command(t_data *data)
{
    pid_t pid;
    char *path;

    pid = fork();
    if (pid == 0)
    {
        // Convert matrix_input to path and arguments
        path = get_path(data->matrix_input[0]);

        if (execve(path, data->matrix_input, data->env) == -1)
        {
            perror("minishell");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    else
    {
        perror("fork failed");
    }
}
