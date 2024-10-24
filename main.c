/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:31:43 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/07 16:41:30 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	
	(void)argc;
	(void)argv;
	char *history;
	data = initialize_data(env);
	while(1)
	{
		data.original_input = readline("Minishell$ "); 
		data = parsing(data);
		if (data.original_input)
            add_history(data.original_input);
		while (data.flag1 == 1 || data.flag2 == 1)
		{
			history = calloc(1, sizeof(char) * ft_strlen(data.original_input) + 1);
			ft_strlcpy(history, data.original_input, ft_strlen(data.original_input) + 1);
			data.original_input = readline("> ");
			if (data.original_input)
			{
				ft_realloc(history, ft_strlen(data.original_input) + ft_strlen(history) + 2);
				history[ft_strlen(history)] = '\n';
				ft_strlcpy(&history[ft_strlen(history) + 1], data.original_input, ft_strlen(data.original_input) + 1);
				add_history(history);
			}
			data = parsing(data);	
		}
		if(ft_strcmp("exit", data.matrix_input[0]) == 0)
		{
			rl_clear_history();
			free_all(&data);
			break;
		}
		else
		{
			execute_command(&data);
			free_input(&data);
		}
	}	
	return (0);
}
