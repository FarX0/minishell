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

void	export(t_data *data)
{
	int		j;
	int		i;
	char	*substr;

	// for now works only with one variable
	j = 0;
	i = 0;
	if (data->matrix_input[2] == NULL) // if there are no arguments, print the environment
	{
		print_export(*data); // funzione da finire
		return ;
	}
	while (data->matrix_input[2][j])
	{
		if (data->matrix_input[2][j] == '_' && data->matrix_input[2][j + 1] == '=')
		{
			while (data->matrix_input[2][j] != '\0' && data->matrix_input[2][j] != ' ')
				j++;
			if (data->matrix_input[2][j] == ' ')
				j++;
		}
		else
		{
			if (ft_isdigit(data->matrix_input[2][j]) || data->matrix_input[2][j] == '=')
			{
				while (data->matrix_input[2][j] != '\0' && data->matrix_input[2][j] != ' ')
					j++;
				i = j - 1;// da miodificare
				while (data->matrix_input[2][i] != '\0' && data->matrix_input[2][i] != ' ' && i != 0)
					i--;
				substr = ft_substr(data->matrix_input[2], i, j - i);
				printf("i = %d, j = %d\n", i, j);
				ft_printf("minishell: export: `%s': not a valid identifier\n", substr);
			}
			else
			{
				while (ft_isalnum(data->matrix_input[2][j]) || data->matrix_input[2][j] == '_')
					j++;
				if (data->matrix_input[2][j] == '=')
				{
					j++;
					while (data->matrix_input[2][j] != '\0' && data->matrix_input[2][j] != ' ')
						j++;
				}
				if (data->matrix_input[2][j] == '\0')
				{
					env_modification(data, j, i);
					return ;
				}
				if (data->matrix_input[2][j] == ' ')
				{
					env_modification(data, j, i);
					j++;
				}
				i = j;
			}
		}
	}
	/* while (data->matrix_input[2][j] != '\0')
		j++; */
	return ;
}

void	env_modification(t_data *data, int j, int x)
{
	char *strcpy;
	int i;
	int pos_eq;

	i = 0;
	strcpy = ft_calloc(sizeof(char), j - x + 1);
	ft_strlcpy(strcpy, &data->matrix_input[2][x], j - x + 1);
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
