/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2024/11/22 15:01:42 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_data *data)
{
	int	i;
	int	arg;

	i = 0;
	arg = 1;
	if (data->matrix_input[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (data->matrix_input[1][i] && strcmp(&data->matrix_input[2][i],"-n") == 0)
		i++;
	while (data->matrix_input[arg])
	{
		while (data->matrix_input[arg][i])
		{
			if ((data->matrix_input[arg][i] == '\"' || data->matrix_input[arg][i] == '\'') && data->matrix_input[arg][i + 1] == '\0')
				break ;
			else if (data->matrix_input[arg][i] == '\"'|| data->matrix_input[arg][i] == '\'')// per non stampare le virgolette
				i++;
			else
			{
				printf("%c", data->matrix_input[arg][i]);
				i++;
			}
		}
		arg++;
		i = 0;
	}
	printf("\n");
}
