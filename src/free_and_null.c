/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:05:16 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/27 15:04:55 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fds(t_data *data)
{
	int	i;

	if (data->fds == NULL)
		return ;
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
	data->exit_code = 0;
	data->error = false;
	rl_clear_history();
}

void	free_cube_input(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nbr_cmd)
	{
		j = 0;
		while (data->cube_input[i][j] != NULL)
		{
			free(data->cube_input[i][j]);
			data->cube_input[i][j] = NULL;
			j++;
		}
		free(data->cube_input[i]);
		data->cube_input[i] = NULL;
		i++;
	}
	free(data->cube_input);
	data->cube_input = NULL;
}

void	free_input(t_data *data)
{
	if (data->cube_input)
	{
		free_cube_input(data);
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
	unlink(".heredoc");
}

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env == NULL)
		return ;
	while (data->env[i] != NULL)
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	free(data->env);
	data->env = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

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
