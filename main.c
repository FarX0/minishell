/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:31:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/28 15:52:49 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_execute(t_data *data, t_variables *var);

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_variables	var;

	(void)argc;
	(void)argv;
	var = (t_variables){0, 0, 0, 0};
	data = initialize_data(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
	while (true)
	{
		data.terminal_input = readline("Minishell$ ");
		if (g_lobal != 0)
			data.exit_code = g_lobal;
		if (data.terminal_input)
			add_history(data.terminal_input);
		else
		{
			ft_printf("exit\n");
			free_all(&data);
			break ;
		}
		start_execute(&data, &var);
	}
	return (0);
}

void	start_execute(t_data *data, t_variables *var)
{
	int	status;
	int	i;

	i = 0;
	*data = parsing(*data, *var);
	if (data->error == true || g_lobal == 130)
	{
		data->exit_code = g_lobal;
		data->error = false;
		g_lobal = 0;
		return (free_input(data));
	}
	while (i < data->nbr_cmd)
		execute_command(data, i++, data->cube_input);
	if (data->nbr_cmd > 1 || !is_builtin(data->cube_input[0][0]))
	{
		waitpid(data->l_pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = WTERMSIG(status) + 128;
		while (i-- > 1)
			waitpid(-1, &status, 0);
	}
	free_input(data);
}

void	sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
