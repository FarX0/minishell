/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2024/09/09 16:18:01 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_echo(t_data *data)
{
	int i = 0;
	int j = 1;
	int flag = 0;

	if (data->matrix_input[j] == NULL)
		{
			printf("\n");
			return;
		}
	if (data->matrix_input[j] && ft_strncmp(data->matrix_input[j], "-n", 2) == 0) //-n
		{
			flag = 1;
			i += 2;
		}
	while (data->matrix_input[j])
	{
		while (data->matrix_input[j][i])
		{
			/* if ((data->matrix_input[j][i] == '\"' || data->matrix_input[j][i] == '\'') && data->matrix_input[j][i + 1] == '\0')
				break; */
			if (data->matrix_input[j][i] == '\"' || data->matrix_input[j][i] == '\'')//controllo correzione
				i++;
			else
			{
				printf("%c", data->matrix_input[j][i]);
				i++;
			}
		}
		i = 0;
		j++;
	}
	if (flag == 0)
		printf("\n");
}
