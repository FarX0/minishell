/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:34:38 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/23 17:13:12 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	same_name(char *envp, char *to_find)//
{
	int	i;

	i = 0;
	while (envp[i] != '=' && to_find[i] != '\0')
	{
		if (envp[i] != to_find[i])
			return (FALSE);
		i++;
	}
	if (envp[i] == '=' && to_find[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	find_in_env(char **envp, char *to_find)
{
	int	n;

	n = 0;
	if (ft_strlen(to_find) == 0)
		return (-1);
	while (envp[n])
	{
		if (ft_strncmp(envp[n], to_find, ft_strlen(to_find)) == 0
			|| same_name(envp[n], to_find) == TRUE)
			return (n);
		n++;
	}
	return (-1);
}

char	*dollar_expansion(t_data data)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*env_value;
	char	*str = NULL;

	i = 0;
	while (data.input[i] != '\0')
	{
		if (data.input[i] == '$' && data.input[i + 1] != '\0')
		{
			j = i + 1;
			while ((ft_isalnum(data.input[j]) || data.input[j] == '_') && data.input[j] != '\0')
				j++;
			l = j - i - 1;
			str = ft_substr(data.input, i + 1, l);
			k = find_in_env(data.env, str);
			if (k != -1 && data.env[k][ft_strlen(str)] == '=')
			{
				env_value = ft_substr(data.env[k], ft_strlen(str) + 1, ft_strlen(data.env[k]) - ft_strlen(str) - 1);
				free(str);
				str = find_and_replace(data.input, env_value, i, l + 1); 
				free(env_value);
			}
			else
			{
				free(str);
				str = find_and_replace(data.input, "", i, l + 1);
			}
		}
		i++;/// i va a 0 why bohbAV'PDF
	}
	return (str);
}

char	**mat_command(t_data *data, int index)
{
	int		i;
	char	**matrix;

	i = 0;
	while (data->cube_input[index][i] != NULL)
		i++;
	matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (data->cube_input[index][i] != NULL)
	{
		matrix[i] = ft_strdup(data->cube_input[index][i]);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
