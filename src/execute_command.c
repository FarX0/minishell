/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2025/02/27 10:18:45 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_cmd(t_data *data)
{
	int i;
	char *x;
	char *s;
	char **search_paths;
	char *env_path;
	char *tmp;

	i = 0;
	if (data->cube_input[0][0][0] == '.' || data->cube_input[0][0][0] == '/')
		handle_relative_path(data);
	tmp = till_redirection(data->cube_input[0][0]);
	x = ft_strjoin("/", tmp);
	free(tmp);
	env_path = get_env_value(data->env, "PATH");
	search_paths = ft_split(env_path, ':');
	free(env_path);
	while (search_paths[i])
	{
		s = ft_strjoin(search_paths[i], x);
		if (is_executable(s)) // le cartelle possono essere eseguite
		{
			data->path = ft_strdup(s);
			free(s);
			free(x);
			free_matrix(search_paths);
			return (1);
		}
		free(s);
		i++;
	}
	free(x);
	free_matrix(search_paths);
	return (0);
}

void dup_fds(t_data *data)
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

/* int wait_pids(pid_t *pid, int nbr_cmds, int *status)
{
	int i;

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
} */

bool is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("cd", cmd) == 0 || ft_strcmp("pwd", cmd) == 0 || ft_strcmp("export", cmd) == 0 || ft_strcmp("unset", cmd) == 0 || ft_strcmp("env", cmd) == 0 || ft_strcmp("exit", cmd) == 0)
		return (true);
	return (false);
}

void run_builtin(t_data *data, int cmd_idx, char **args)
{
	(void)cmd_idx;
	if (!args[0])
		return;
	if (ft_strcmp("echo", args[0]) == 0)
		data->exit_code = builtin_echo(data, args);
	else if (ft_strcmp("cd", args[0]) == 0)
		data->exit_code = builtin_cd(data, args);
	else if (ft_strcmp("pwd", args[0]) == 0)
		data->exit_code = pwd();
	else if (ft_strcmp("export", args[0]) == 0)
		data->exit_code = export(data, args);
	else if (ft_strcmp("unset", args[0]) == 0)
		data->exit_code = builtin_unset(data, args);
	else if (ft_strcmp("env", args[0]) == 0)
		data->exit_code = print_matrix(data->env);
	else if (ft_strcmp("exit", args[0]) == 0)
		builtin_exit(data, args);
}

void run_in_fork(t_data *data, int cmd_idx, char **args)
{
	pid_t pid;
	char	**matrix;

	pid = fork();
	if (pid != 0)
		return;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup_fds(data);
	if (is_builtin(args[0]))
	{
		run_builtin(data, cmd_idx, args);
		free_all(data);
		exit(data->exit_code);
	}
	matrix = mat_command(data, cmd_idx);
	execve(data->path, matrix, data->env);
	free_all(data);
}

int execute_command(t_data *data, int cmd_idx, char **args)
{
	bool is_a_builtin;
	// fd[1] -> stdout
	// fd[0] -> stdin
	is_a_builtin = is_builtin(args[0]);
	if (data->nbr_cmd == 1 && is_a_builtin)
	{
		run_builtin(data, cmd_idx, args);
		return (data->exit_code);
	}
	if (!is_a_builtin)
		search_cmd(data);
	if (!is_a_builtin && !data->path)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_code = 127;
		return (data->exit_code);
	}
	run_in_fork(data, cmd_idx, args);
	return (0);
}

int print_matrix(char **matrix)
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
