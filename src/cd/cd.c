/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:20:53 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/19 17:14:42 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_data *data)
{
	char	*path;

	if(data->cube_input[0][2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (data->cube_input[0][1] == NULL)
	{
		path = get_env_value(data->env, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = data->cube_input[0][1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->cube_input[0][1], 2);
		ft_printf(": %s\n", strerror(errno), 2);
		return (1);
	}
	return (0);
}

char	*get_env_value(char **env, char *key)
{
	int		i;
	int		j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], key, j) == 0)
			return (ft_strdup(env[i] + j + 1));
		i++;
	}
	return (NULL);
}
