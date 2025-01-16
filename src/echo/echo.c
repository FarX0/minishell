/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/01/16 11:37:18 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_data *data)
{
	int	i;

	i = 0;
	int aug = 1; // numero argomenti in modo che ogni ciclo prende un argomrnto
	if (data->cube_input[0][1] == NULL)
	{
		printf("\n");
		return ;
	}
	while(data->cube_input[0][aug])
	{
		data->cube_input[0][aug] = dollar_red(data->cube_input[0][aug], data);
		aug++;
	}
	aug = 1;
	dollar_red(data->cube_input[0][aug], data);
	while (data->cube_input[0][aug])
	{
		if (data->cube_input[0][aug][i] && strcmp(&data->cube_input[0][aug][i],"-n") == 0) //-n
			i++;
		while (data->cube_input[0][aug][i])
		{
			if ((data->cube_input[0][aug][i] == '\"'
					|| data->cube_input[0][aug][i] == '\'')
					&& data->cube_input[0][aug][i + 1] == '\0')
				break ;
			else if (data->cube_input[0][aug][i] == '\"'
				|| data->cube_input[0][aug][i] == '\'')
				i++;
			else
			{
				printf("%c", data->cube_input[0][aug][i]);
				i++;
			}
		}
		i = 0;
		aug++;
		printf(" ");
	}
	printf("\n");
}
