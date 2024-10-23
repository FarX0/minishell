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

	if(data->matrix_input[2] == NULL)
	{
		printf("\n");
		return;
	}
    if (data->matrix_input[2][i] && strcmp(&data->matrix_input[2][i], "-n") == 0)//-n
        i++;
    while (data->matrix_input[2][i])
    {
		if ((data->matrix_input[2][i] == '\"' || data->matrix_input[2][i] == '\'')
			&& data->matrix_input[2][i + 1] == '\0')
			break;
		else if (data->matrix_input[2][i] == '\"' || data->matrix_input[2][i] == '\'')
			i++;
        else
		{
			printf("%c", data->matrix_input[2][i]);
        	i++;
		}
    }
    printf("\n");
}
