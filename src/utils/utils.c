/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/12/20 15:22:53 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int size)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), size);
	ft_strlcpy(new_str, str, size);
	free(str);
	return (new_str);
}

char	*dollar_red(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*var_name;
	char	*new_str;
	char	*var_value;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			var_name = ft_substr(str, i + 1, j - i - 1);
			var_value = get_env_value(data->env, var_name);
			free(var_name);
			if (var_value)
			{
				new_str = malloc(ft_strlen(str) - (j - i) + ft_strlen(var_value)
						+ 1);
				ft_strlcpy(new_str, str, i + 1);
				ft_strlcat(new_str, var_value, ft_strlen(new_str)
					+ ft_strlen(var_value) + 1);
				ft_strlcat(new_str, &str[j], ft_strlen(new_str)
					+ ft_strlen(&str[j]) + 1);
				free(str);
				return (new_str);
			}
		}
		i++;
	}
	return (str);
}

int	is_executable(char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) == -1)
		return (0);
	if ((S_ISREG(path_stat.st_mode) && (path_stat.st_mode & S_IXUSR))
		&& !S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

void	handle_relative_path(t_data *data)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (data->cube_input[0][i])
	{
		if (data->cube_input[0][i][0] == '.' && data->cube_input[0][i][1] == '/')
		{
			path = ft_strjoin(data->path, "/");
			tmp = ft_strjoin(path, data->cube_input[0][i]);
			free(path);
			if (is_executable(tmp))
			{
				free(data->cube_input[0][i]);
				data->cube_input[0][i] = ft_strdup(tmp);
			}
			free(tmp);
		}
		i++;
	}
}
