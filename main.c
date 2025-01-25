/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:31:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/24 18:03:09 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_variables	var;
	int			status;
	
	(void)argc;
	(void)argv;
	var = (t_variables){0, 0, 0, 0};
	data = initialize_data(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
	while(true)
	{
		data.terminal_input = readline("Minishell$ ");
		if (g_lobal != 0)
			data.exit_code = g_lobal;
		if (data.terminal_input)
			add_history(data.terminal_input);
		else
		{
			ft_printf("exit\n");
			rl_clear_history();
			free_all(&data);
			break;
		}
		data = parsing(data, var);
		if(data.error == true)
		{
			free_input(&data);
			continue;
		}
		if(ft_strcmp("exit", data.cube_input[0][0]) == 0 && data.cube_input[0][2] == NULL)
			rl_clear_history();
		int i = -1;
		while (++i < data.nbr_cmd)
		{
			execute_command(&data, i, data.cube_input[i]);
		}
		while (waitpid(-1, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				data.exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data.exit_code = WTERMSIG(status)+128;
		}
		free_input(&data);
	}
	return (0);
}


void	sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
