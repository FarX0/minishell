/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/19 15:51:23 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            handle_redirection(data, i, ">");
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], "<") == 0)
        {
            handle_redirection(data, i, "<");
            break;
        }
        else if (ft_strcmp(data->matrix_input[i], ">>") == 0)
        {
            handle_redirection(data, i, ">>");
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
