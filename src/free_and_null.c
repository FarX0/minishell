/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:05:16 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/18 16:23:31 by tfalchi          ###   ########.fr       */
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
	if (data->matrix_input)
	{
		
		int i = 0;
		while (data->matrix_input[i] != NULL)
		{
			printf("Freeing matrix input:%s\n", data->matrix_input[i]);
			free(data->matrix_input[i]);
			data->matrix_input[i] = NULL;
			i++;
		}
		free(data->matrix_input);
		data->matrix_input = NULL;
	}
	if (data->input)
	{
		printf("Freeing input:%s\n", data->input);
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