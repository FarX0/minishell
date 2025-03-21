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

char	*till_redirection(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\0')
		i++;
 	new = malloc(sizeof(char) * i + 1);//leak da risolvere (definately lost)
	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

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
	while (i != start && str_og[i])
		str[j++] = str_og[i++];
	while (str_og[i])
	{
		if (i == start)
		{
			while (new[k])
				str[j++] = new[k++];
			i += ignore;
			break;
		}
	}
	while (str_og[i])
		str[j++] = str_og[i++];
	str[j] = '\0';
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

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while(str[i] != 39)
			{
				new[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		else if (str[i] == 34)
		{
			i++;
			while(str[i] != 34)
			{
				new[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			new[j] = str[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	free(str);
	return (new);
}
