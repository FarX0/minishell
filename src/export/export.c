/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:39:47 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/27 14:44:46 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *data, char **args)
{
	int	j;
	int	aug;
	int	return_value;

	aug = 1;
	j = 0;
	return_value = 0;
	if (args[aug] == NULL)
	{
		print_export(*data);
		return (0);
	}
	while (args[aug])
	{
		while (args[aug][j])
		{
			if (args[aug][j] == '_' && args[aug][j + 1] == '=')
			{
				while (args[aug][j] != '\0' && args[aug][j] != ' ')
					j++;
				if (args[aug][j] == ' ')
				{
					j++;
					continue ;
				}
				else
					return (return_value);
			}
			if (ft_isdigit(args[aug][j]) || args[aug][j] == '=')
			{
				return_value = 1;
				while (args[aug][j] != '\0' && args[aug][j] != ' ')
					j++;
				ft_printf("minishell: export: `%s': not a valid identifier\n",
					args[aug]);
				continue ;
			}
			else
			{
				while (ft_isalnum(args[aug][j]) || args[aug][j] == '_')
					j++;
				if (args[aug][j] == '=')
				{
					j++;
					while (args[aug][j] != '\0' && args[aug][j] != ' ')
						j++;
				}
				if (args[aug][j] == '\0')
					env_modification(data, j, aug, args);
				if (args[aug][j] == ' ')
				{
					env_modification(data, j, aug, args);
					j++;
					continue ;
				}
			}
		}
		aug++;
		j = 0;
	}
	return (return_value);
}

/*
	if (ft_strncmp(data->env[i], strcpy, pos_eq) == 0)
	if the variable is already in the environment, update it

	if the variable is not in the environment, realloc the environment
	data->env[i] = ft_strdup(strcpy); and add the variable
*/
void	env_modification(t_data *data, int j, int aug, char **args)
{
	char	*strcpy;
	int		i;
	int		pos_eq;
	int		is_present;

	is_present = 0;
	i = 0;
	strcpy = ft_calloc(sizeof(char), j + 1);
	ft_strlcpy(strcpy, args[aug], j + 1);
	pos_eq = ft_strchr(strcpy, '=') - strcpy;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], strcpy, pos_eq) == 0)
		{
			free(data->env[i]);
			data->env[i] = NULL;
			data->env[i] = ft_strdup(strcpy);
			free(strcpy);
			return ;
		}
		if (ft_strncmp(data->env[i], strcpy, ft_strchr(data->env[i], '=')
				- data->env[i]) == 0)
			is_present = 1;
		i++;
	}
	if (is_present == 0)
	{
		data->env = realloc_env(*data);
		data->env[i] = ft_strdup(strcpy);
	}
	free(strcpy);
	strcpy = NULL;
}
