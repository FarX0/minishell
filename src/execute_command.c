/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/09 11:13:22 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_data *data) //funzione che esegue i built-in
{
	if (ft_strcmp("echo", data->matrix_input[0]) == 0)
		builtin_echo(data);
	else if (ft_strcmp("cd", data->matrix_input[0]) == 0)
		printf("cd\n");
	else if(ft_strcmp("pwd", data->matrix_input[0]) == 0)
		pwd();
	else if (ft_strcmp("export", data->matrix_input[0]) == 0)
		export(data);
	else if (ft_strcmp("unset", data->matrix_input[0]) == 0)
		printf("unset\n");
	else if (ft_strcmp("env", data->matrix_input[0]) == 0) 
		print_matrix(data->env);
}

void	print_matrix(char **matrix) 
{
	int i;

	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}
