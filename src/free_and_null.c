/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:05:16 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/07 11:44:50 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_all(t_data *data)
{
	free_input(data);
	free_env(data);
}

void free_input(t_data *data)
{
	/* if (data->matrix_input)
	{
		printf("Freeing input: %s\n", data->matrix_input);
		free(data->matrix_input);
		data->matrix_input = NULL;
	} */
	if (data->matrix_input)
	{
		
		int i = 0;
		while (data->matrix_input[i] != NULL)
		{
			printf("Freeing input: %s\n", data->matrix_input[i]);
			free(data->matrix_input[i]);
			data->matrix_input[i] = NULL;
			i++;
		}
		free(data->matrix_input);
		data->matrix_input = NULL;
	}
	if (data->input)
	{
		printf("Freeing original_input: %s\n", data->input);
		free(data->input);
		data->input = NULL;
	}
}

void free_env(t_data *data)
{
	int i;

	i = 0;
	if (data->env == NULL)
		return;
	while (data->env[i] != NULL)
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	free(data->env);
	data->env = NULL;
}