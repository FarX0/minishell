/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/01/24 17:00:44 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	int aug = 1; // numero argomenti in modo che ogni ciclo prende un argomrnto
	if (data->cube_input[0][1] == NULL)
	{
		printf("\n");
		return (0);
	}
	/* while(data->cube_input[0][aug])
		aug++; 
	aug = 1;*/
	while (data->cube_input[0][aug])
	{
		if (data->cube_input[0][aug][i] && strcmp(&data->cube_input[0][aug][i],"-n") == 0) //-n
			i++;
		while (data->cube_input[0][aug][i])
		{
			if (data->cube_input[0][aug][i] == '\"' || data->cube_input[0][aug][i] == '\'')
			{
				n = i + 1;
				i = skip_quotes(data->cube_input[0][aug], i);
				while (n < i - 1)
				{
					printf("%c", data->cube_input[0][aug][n]);
					n++;
				}
			}
			else
			{
				printf("%c", data->cube_input[0][aug][i]);
				i++;
			}
		}
		i = 0;
		if (data->cube_input[0][aug + 1] != NULL && data->cube_input[0][aug][0] != '\0')
			printf(" ");
		aug++;
	}
	printf("\n");
	return (0);
}
