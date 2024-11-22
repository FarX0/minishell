/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2024/11/18 18:42:41 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_data *data)
{
	int	i;

	i = 0;
	int aug = 1; // numero argomenti in modo che ogni ciclo prende un argomrnto
	if (data->matrix_input[1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (data->matrix_input[aug])
	{
		if (data->matrix_input[aug][i] && strcmp(&data->matrix_input[aug][i],"-n") == 0) //-n
			i++;
		while (data->matrix_input[aug][i])
		{
			if ((data->matrix_input[aug][i] == '\"'
					|| data->matrix_input[aug][i] == '\'')
					&& data->matrix_input[aug][i + 1] == '\0')
				break ;
			else if (data->matrix_input[aug][i] == '\"'
				|| data->matrix_input[aug][i] == '\'')
				i++;
			else
			{
				printf("%c", data->matrix_input[aug][i]);
				i++;
			}
		}
		i = 0;
		aug++;
		printf(" ");
	}
	printf("\n");
}
