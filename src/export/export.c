/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:39:47 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/10 12:18:06 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(t_data *data)	// if no arguments, print the environment, otherwise env_modification
{
	int i;
	int j;
	//	char *substr;

	// for now works only with one variable
	i = 0;
	j = 1;
	if (data->matrix_input[j] == NULL) // if there are no arguments, print the environment
	{
		print_export(*data);
		return;
	}
	while (data->matrix_input[j])
	{
		while (data->matrix_input[j][i] == '_' && data->matrix_input[j][i + 1] == '=')
			j++;
		while (ft_isdigit(data->matrix_input[j][0]) || data->matrix_input[j][0] == '=')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", data->matrix_input[j]);
			j++;
		}
		while (ft_isalnum(data->matrix_input[j][i]) || data->matrix_input[j][i] == '_')
			i++;
		while (data->matrix_input[j][i] != '\0')
			i++;
		env_modification(data, j);
		j++;
	}
	/* while (data->matrix_input[j][i] != '\0')
		i++; */
	return;
}

void env_modification(t_data *data, int j)// ifvariable  exists, update it, otherwise add it
{
	char *strcpy;
	int i;
	int pos_eq;//posizione dell '='

	i = 0;
	strcpy = ft_strdup(data->matrix_input[j]);
	pos_eq = ft_strchr(data->matrix_input[j], '=') - data->matrix_input[j];
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], strcpy, pos_eq) == 0)// if the variable is already in the environment, update it
		{
			free(data->env[i]);
			data->env[i] = NULL;
			data->env[i] = ft_strdup(strcpy);
			free(strcpy);
			return;
		}
		i++;
	}
	data->env = realloc_env(*data);
	// if the variable is not in the environment, realloc the environment
	data->env[i] = ft_strdup(strcpy); // and add the variable
	free(strcpy);
	strcpy = NULL;
	return;
}
