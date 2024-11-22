/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:27:20 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/22 14:39:52 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	initialize_data(char **env)
{
	t_data	data;

	data.env = matrix_dup(env);
	data.matrix_input = NULL;
	data.input = NULL;
	data.flag1 = 0;
	data.flag2 = 0;
	return (data);
}

char	**matrix_dup(char **matrix)
{
	char	**new_matrix;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}
