/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:58:33 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/22 15:26:46 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle the redirections: >, <, >>, <<
void handle_redirection(t_data *data, int i, char *redir)
{
    int fd;
    
    if (strcmp(redir, ">>") == 0 || strcmp(redir, ">") == 0)
    {
        if (strcmp(redir, ">") == 0)
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
    else if (strcmp(redir, "<") == 0)
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

// Execute the command using execve
void execve_command(t_data *data)
{
    pid_t	pid;
    char	*path;

    pid = fork();
    if (pid == 0)
    {
		//lofiorin get path
        // Convert matrix_input to path and arguments
        /* path = get_path(data->matrix_input[0]);
        if (execve(path, data->matrix_input, data->env) == -1)
        {
            perror("minishell");
            exit(1);
        } */
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
