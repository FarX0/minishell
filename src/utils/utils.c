/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuele <samuele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/25 20:58:11 by samuele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_and_replace(char *str_og, char *new, int start, int ignore)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(ft_strlen(str_og) + ft_strlen(new) - ignore + 1);
	while (str_og[i])
	{
		if (i == start)
		{
			while (new[k])
				str[j++] = new[k++];
			i += ignore;
		}
		while (i != start && str_og[i])
			str[j++] = str_og[i++];
	}
	str[j] = '\0';
	free(str_og);
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
