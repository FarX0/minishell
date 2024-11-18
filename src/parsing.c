/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/18 16:02:35 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data parsing(t_data data)
{
	data = del_extra_spaces(data);
	data = split_input(data);
	return (data);
}

t_data del_extra_spaces(t_data data)
{
	int i;
	int j;
	char *strcpy;

	i = 0;
	j = 0;
	data.input = ft_strdup(data.original_input);
	if (data.input)
		strcpy = ft_calloc(sizeof(char), ft_strlen(data.input) + 1);
	while (data.input[i] == ' ')
		i++;
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39 && data.flag1 % 2 == 0)
			data.flag2 += 1;
		if (data.input[i] == 34 && data.flag2 % 2 == 0)
			data.flag1 += 1; 
		while (data.input[i] == ' ' && data.input[i + 1] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0)
			i++;
		if (data.input[i] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0 && data.input[i + 1] == '\0')
			i++;
		strcpy[j] = data.input[i];
		i++;
		j++;
	}
	free(data.input);
	data.input = strcpy;
	return (data);
}

t_data split_input(t_data data)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (data.input)
		data.matrix_input = matrix_alloc(data.input);
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39) //da fare on un &
		{
			i++;
			while (data.input[i] != 39 && data.input[i] != '\0')
			{
				data.matrix_input[k][j] = data.input[i];
				i++;
				k++;
			}
			i++;
		}
		if (data.input[i] == 34)
		{
			i++;
			while (data.input[i] != 34 && data.input[i] != '\0')
			{
				data.matrix_input[k][j] = data.input[i];
				i++;
				k++;
			}
			i++;
		}
		if (data.input[i] == ' ')//fattibile con split
		{
			data.matrix_input[k][j] = '\0';
			j = 0;
			k++;
			i++;
		}
		if (data.input[i] == '\0')
			break;
		data.matrix_input[k][j] = data.input[i];
		i++;
		j++;
	}
	return (data);
}

char **matrix_alloc(char *str)
{
	int i, j, k;
	char **matrix;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	matrix = ft_calloc(sizeof(char *), k + 2);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] != ' ' && str[i] != '\0')
		{
			i++;
			j++;
		}
		matrix[k] = ft_calloc(sizeof(char), j + 1);
		k++;
		j = 0;
		if (str[i] == '\0')
			break;
		i++;
	}
	return (matrix);
}
