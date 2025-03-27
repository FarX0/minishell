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

int	same_name(char *envp, char *to_find)
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
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	str = ft_strdup(data.input);
	while (data.input[i] != '\0')
	{
		if (data.input[i] == '$' && data.input[i + 1] != '\0' && data.input[i + 1] != ' ')
		{
			if (data.input[i + 1] == '?')
			{
				env_value = ft_itoa(data.exit_code);
				tmp = ft_strdup(str);
				free(str);
				str = find_and_replace(tmp, env_value, i, 2);
				free(tmp);
				tmp = NULL;
				free(env_value);
				env_value = NULL;
				i = i + 2;
				continue ;
			}
			j = i + 1;
			while ((ft_isalnum(data.input[j]) || data.input[j] == '_') && data.input[j] != '\0')
				j++;
			l = j - i - 1;
			tmp = ft_substr(data.input, i + 1, l);
			k = find_in_env(data.env, tmp);
			if (k != -1 && data.env[k][ft_strlen(tmp)] == '=')
			{
				env_value = ft_substr(data.env[k], ft_strlen(tmp) + 1, ft_strlen(data.env[k]) - ft_strlen(tmp) - 1);
				free(tmp);
				tmp = ft_strdup(str);
				free(str);
				str = find_and_replace(tmp, env_value, i, l + 1);
				free(tmp);
				tmp = NULL;
				i = i + l;
				free(env_value);
			}
			else
			{
				free(tmp);
				tmp = ft_strdup(str);
				free(str);
				str = find_and_replace(tmp, "", i, l + 1);
				free(tmp);
				tmp = NULL;
				i = i + l;
			}
		}
		else
			if (data.input[i + 1] == '\0' || data.input[i + 1] == ' ')
				i++;
		i++;
	}
	free(data.input);
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
