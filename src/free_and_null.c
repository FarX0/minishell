/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:05:16 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/16 11:41:46 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fds(t_data *data)
{
	int i;

	if (data->fds == NULL)
		return;
	i = 0;
	while (i < data->nbr_cmd)
    {
        if (data->fds[i] != NULL)
        {
            free(data->fds[i]);
            data->fds[i] = NULL;
        }
        i++;
    }
	free(data->fds);
	data->fds = NULL;
	data->nbr_cmd = 1;
}
void	free_all(t_data *data)
{
	free_input(data);
	free_env(data);
}

void free_input(t_data *data)
{
    if (data->cube_input)
    {
        int n = 0;
        while (data->cube_input[n] != NULL)
        {
            int i = 0;
            while (data->cube_input[n][i] != NULL)
            {
                free(data->cube_input[n][i]);
                data->cube_input[n][i] = NULL;
                i++;
            }
            free(data->cube_input[n]);
            data->cube_input[n] = NULL;
            n++;
        }
        free(data->cube_input);
        data->cube_input = NULL;
    }
    if (data->input)
    {
        free(data->input);
        data->input = NULL;
    }
    if (data->path)
    {
        free(data->path);
        data->path = NULL;
    }
    free_fds(data);
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

void    free_matrix(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i] != NULL)
    {
        free(matrix[i]);
        matrix[i] = NULL;
        i++;
    }
    free(matrix);
    matrix = NULL;
}
