/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/25 15:52:07 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_cmd(t_data *data)
{
	int		i;
	char	*x;
	char	*s;
	char	**paths;
	char	*path;

	i = 0;
	if (data->cube_input[0][0][0] == '.' || data->cube_input[0][0][0] == '/')
		handle_relative_path(data);
	else
	{
		x = ft_strjoin("/", data->cube_input[0][0]); // liberi l'argomento a destra
		path = get_env_value(data->env, "PATH");
		paths = ft_split(path, ':');
		free(path);
		while (paths[i])
		{
			s = ft_strjoin(paths[i], x);
			if (is_executable(s)) // le cartelle possono essere eseguite
			{
				data->path = ft_strdup(s);
				free(s);
				free(x);
				free_matrix(paths);
				return (1);
			}
			free(s);
			i++;
		}
		free(x);
		free_matrix(paths);
	}
	return (0);
}

void	dup_fds(t_data *data)
{
	if (data->fds[0][0] != 0)
	{
		dup2(data->fds[0][0], 0);
		close(data->fds[0][0]);
	}
	if (data->fds[0][1] != 1)
	{
		dup2(data->fds[0][1], 1);
		close(data->fds[0][1]);
	}
}

int	wait_pids(pid_t *pid, int nbr_cmds, int *status)
{
	int	i;

	i = 0;
	while (i < nbr_cmds)
	{
		waitpid(pid[i], status, 0);
		i++;
	}
	free(pid);
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		return (WTERMSIG(*status) + 128);
	return (0);
}

int	execute_command(t_data *data)
{
	pid_t	*pid;
	int		i;
	int		status;

	i = 0;
	// int fd[2];
	// pipe(fd);
	// fd[1] -> stdout
	// fd[0] -> stdin
	pid = malloc(sizeof(pid_t) * 1); // data->nbr_cmd
	if (ft_strcmp("echo", data->cube_input[0][0]) == 0)
		/* data->exit_code = */ builtin_echo(data);
	else if (ft_strcmp("cd", data->cube_input[0][0]) == 0)
		data->exit_code = builtin_cd(data);
	else if (ft_strcmp("pwd", data->cube_input[0][0]) == 0)
		data->exit_code = pwd();
	else if (ft_strcmp("export", data->cube_input[0][0]) == 0)
		data->exit_code = export(data);
	else if (ft_strcmp("unset", data->cube_input[0][0]) == 0)
		data->exit_code = builtin_unset(data);
	else if (ft_strcmp("env", data->cube_input[0][0]) == 0)
		data->exit_code = print_matrix(data->env);
	else if (ft_strcmp("exit", data->cube_input[0][0]) == 0)
		builtin_exit(data);
	else if (ft_strcmp("print", data->cube_input[0][0]) == 0)
	{
		i = 0;
		while (data->cube_input[i])
		{
			print_matrix(data->cube_input[i]);
			i++;
		}
		printf("input = %s\n", data->input);
		
		free_all(data);
	}
	else if (search_cmd(data))
	{
		printf("found on %s\n", data->path);
		while (data->nbr_cmd > i)
		{
			//"ls" "-l"
			// /bin/ls
			// ["ls", NULL]
			pid[i] = fork();
			if (pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				dup_fds(data);
				execve(data->path, data->cube_input[0], data->env);
				free_all(data);
			}
			i++;
		}
		i = 0;
		while(i < data->nbr_cmd)
		{
			waitpid(pid[i], &status, 0);
            if (WIFEXITED(status))
                data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = WTERMSIG(status) + 128;
			i++;
        }
        free(pid);
        return (data->exit_code);
	}
	free(pid);
	return (0);
}

int	print_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	return (0);
}
