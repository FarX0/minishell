/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:20:53 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/28 11:14:16 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_data *data, char **args)
{
	const int	nbr_args = ft_mtxlen(args);
	char		*path;
	bool		is_allocated;

	is_allocated = false;
	path = data->cube_input[0][1];
	if (nbr_args == 1)
	{
		path = get_env_value(data->env, "HOME");
		is_allocated = true;
		if (path == NULL)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	if (nbr_args > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->cube_input[0][1], 2);
		ft_printf(": %s\n", strerror(errno), 2);
		return (1);
	}
	if (is_allocated)
		free(path);
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
