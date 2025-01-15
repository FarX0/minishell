/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:39:47 by tfalchi           #+#    #+#             */
/*   Updated: 2024/12/20 15:22:22 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_data *data)
{
	int		j;
	int		aug = 1;

	j = 0;
	if (data->cube_input[0][aug] == NULL)
	{
		print_export(*data);
		return ;
	}
	while (data->cube_input[0][aug])
	{
		while (data->cube_input[0][aug][j])
		{
			if (data->cube_input[0][aug][j] == '_' && data->cube_input[0][aug][j + 1] == '=')
			{
				while (data->cube_input[0][aug][j] != '\0' && data->cube_input[0][aug][j] != ' ')
					j++;
				if (data->cube_input[0][aug][j] == ' ')
				{
					j++;
					continue;
				}
				else
					return ;
			}
			if (ft_isdigit(data->cube_input[0][aug][j]) || data->cube_input[0][aug][j] == '=')
			{
				while (data->cube_input[0][aug][j] != '\0' && data->cube_input[0][aug][j] != ' ')
					j++;
				ft_printf("minishell: export: `%s': not a valid identifier\n", data->cube_input[0][aug]);
				continue;
			}
			else
			{
				while (ft_isalnum(data->cube_input[0][aug][j]) || data->cube_input[0][aug][j] == '_')
					j++;
				if (data->cube_input[0][aug][j] == '=')
				{
					j++;
					while (data->cube_input[0][aug][j] != '\0' && data->cube_input[0][aug][j] != ' ')
						j++;
				}
				if (data->cube_input[0][aug][j] == '\0')
					env_modification(data, j, aug);
				if (data->cube_input[0][aug][j] == ' ')
				{
					env_modification(data, j, aug);
					j++;
					continue;
				}
			}
		}
		aug++;
		j = 0;
	}
	return ;
}

void	env_modification(t_data *data, int j, int aug)
{
	char *strcpy;
	int i;
	int pos_eq;

	i = 0;
	strcpy = ft_calloc(sizeof(char), j + 1);
	ft_strlcpy(strcpy, data->cube_input[0][aug], j + 1);
	pos_eq = ft_strchr(strcpy, '=') - strcpy;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], strcpy, pos_eq) == 0)
		// if the variable is already in the environment, update it
		{
			free(data->env[i]);
			data->env[i] = NULL;
			data->env[i] = ft_strdup(strcpy);
			free(strcpy);
			return ;
		}
		i++;
	}
	data->env = realloc_env(*data);
	// if the variable is not in the environment, realloc the environment
	data->env[i] = ft_strdup(strcpy); // and add the variable
	free(strcpy);
	strcpy = NULL;
	return ;
}
