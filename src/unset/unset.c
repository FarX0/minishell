/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:28:26 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/19 17:37:20 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_unset(t_data* data, char** args)
{
	int		i;
	int		j;
	int		k;
	char	**new_matrix;
	int		return_value;

	i = 0;
	j = 0;
	k = 1;
	return_value = 0;
	if (args[k] == NULL)
		return (0);
	while (args[k])
	{
		while(args[k][i])
		{
			if (args[k][i] == '_' && args[k][i + 1] == '=')
			{
				k++;
				continue;
			}
			if (ft_isdigit(args[k][i]) || args[k][i] == '=')
			{
				return_value = 1;
				while (args[k][i] != '\0' && args[k][i] != ' ')
					i++;
				ft_printf("minishell: export: `%s': not a valid identifier\n", args[k]);
				continue;
			}
			i++;
		}
		if (find_in_env(data->env, args[k]) != -1)
		{
			i = 0;
			while (args[i] && args[k] != args[i])
			{
				if (ft_strncmp(args[k], args[i], longest_string(args[k], args[i])) == 0)
					j--;
				i++;
			}
			j++;
			printf("found %s\n", args[k]);
		}
		k++;
	}
	while (data->env[i])
		i++;
	if (i - j > 0)
	{
		new_matrix = malloc(sizeof(char *) * (i - j + 1));
		data->env = env_dup(new_matrix, data, args);
	}
	else
		new_matrix = NULL;
	//free_matrix(new_matrix);
	return (return_value);
}

char** env_dup(char** matrix, t_data* data, char** args)
{
	int	n;
	int	k;
	int	j;
	int	i;
	bool b;

	n = 0;
	j = 0;
	while (data->env[n])
	{
		b = false;
		k = 1;
		while (args[k])
		{
			i = 1;
			while (args[k][i] != '\0')
				i++;
			if (strncmp(data->env[n], args[k], i) == 0)
				b = true;
			k++;
		}
		if (b == false)
		{
			matrix[j] = ft_strdup(data->env[n]);
			j++;
		}
		n++;
	}
	matrix[j] = NULL;
	free_matrix(data->env);
	data->env = matrix;
	return (matrix);
}

int		longest_string(char *str1, char *str2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
		i++;
	while (str2[j] != '\0')
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}
