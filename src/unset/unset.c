/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:28:26 by tfalchi           #+#    #+#             */
/*   Updated: 2024/12/20 15:22:37 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	**new_matrix;

	i = 0;
	j = 0;
	k = 1;
	if (data->cube_input[0][k] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	while (data->cube_input[0][k])
	{
		while(data->cube_input[0][k][i])
		{
			if (data->cube_input[0][k][i] == '_' && data->cube_input[0][k][i + 1] == '=')
			{
				k++;
				continue;
			}
			if (ft_isdigit(data->cube_input[0][k][i]) || data->cube_input[0][k][i] == '=')
			{
				while (data->cube_input[0][k][i] != '\0' && data->cube_input[0][k][i] != ' ')
					i++;
				ft_printf("minishell: export: `%s': not a valid identifier\n", data->cube_input[0][k]);
				continue;
			}
			i++;
		}
		if (find_in_env(data->env, data->cube_input[0][k]) != -1)
		{
			i = 0;
			while (data->cube_input[0][i] && data->cube_input[0][k] != data->cube_input[0][i])
			{
				if (ft_strncmp(data->cube_input[0][k], data->cube_input[0][i], longest_string(data->cube_input[0][k], data->cube_input[0][i])) == 0)
					j--;
				i++;
			}
			j++;
			printf("found %s\n", data->cube_input[0][k]);
		}
		k++;
	}
	while (data->env[i])
		i++;
	if (i - j > 0)
	{
		new_matrix = malloc(sizeof(char *) * (i - j + 1));
		data->env = env_dup(new_matrix, data);
	}
	else
		new_matrix = NULL;
}

char	**env_dup(char **matrix, t_data *data)
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
		while (data->cube_input[0][k])
		{
			i = 1;
			while (data->cube_input[0][k][i] != '\0')
				i++;
			if (strncmp(data->env[n], data->cube_input[0][k], i) == 0)
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
