/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:11:12 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/28 13:59:43 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data data)
{
	int		i;
	char	**temp_env;
	char	*temp_str;

	i = 0;
	temp_env = sort_env(data);
	while (temp_env[i] != NULL)
	{
		if ((temp_str = ft_strchr(temp_env[i], '=')) != NULL)
		{
			*temp_str = '\0';
			ft_printf("declare -x %s=\"%s\"\n", temp_env[i], temp_str + 1);
			*temp_str = '=';
		}
		else
		{
			ft_printf("declare -x %s\n", temp_env[i]);
		}
		free(temp_env[i]);
		i++;
	}
	free(temp_env);
}

char	**sort_env(t_data data)
{
	int		i;
	int		j;
	char	**temp_env;
	char	*temp;
	int		env_size;

	env_size = 0;
	while (data.env[env_size] != NULL)
		env_size++;
	temp_env = (char **)malloc((env_size + 1) * sizeof(char *));
	i = 0;
    while (i < env_size)
    {
		temp_env[i] = ft_strdup(data.env[i]);
		if (!temp_env[i])
		{
			while (i > 0)
				free(temp_env[--i]);
			free(temp_env);
			return (NULL);
		}
		i++;
	}
	temp_env[env_size] = NULL;
	i = 0;
    while (i < env_size - 1)
    {
		j = 0;
		while (j < env_size - i - 1)
        {
			if (strcmp(temp_env[j], temp_env[j + 1]) > 0)
			{
				temp = temp_env[j];
				temp_env[j] = temp_env[j + 1];
				temp_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (temp_env);
}

char	**realloc_env(t_data data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data.env[i] != NULL)
		i++;
	new_env = calloc(sizeof(char *), i + 2);
	i = 0;
	while (data.env[i] != NULL)
	{
		new_env[i] = ft_strdup(data.env[i]);
		i++;
	}
	free_env(&data);
	return (new_env);
}
