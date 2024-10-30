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
	//char *history;
	data = initialize_data(env);
	while(1)
	{
		data.original_input = readline("Minishell$ "); //legge l'input e lo salva in original_input stampando Minishell$
		data = parsing(data);
		if (data.original_input)
            add_history(data.original_input);//aggiunge l'input alla history
		print_matrix(data.matrix_input);
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
