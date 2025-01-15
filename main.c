/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:31:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/15 17:51:12 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint();

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_variables	var;
	
	(void)argc;
	(void)argv;
	var = (t_variables){0, 0, 0, 0};
	data = initialize_data(env);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, sigint);
	while(true)
	{
		data.terminal_input = readline("Minishell$ ");
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
		if(ft_strcmp("exit", data.cube_input[0][0]) == 0)
		{
			rl_clear_history();
			free_all(&data);
			break;
		}
		else
		{
			data.exit_code = execute_command(&data);
			printf("exit code: %d\n", data.exit_code);
			free_input(&data);
		}
	}	
	return (0);
}


void	sigint()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
