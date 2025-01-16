/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/16 12:20:34 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	parsing(t_data data, t_variables var)
{
	data = del_extra_spaces(data);
	data = split_input(data, var);
	return (data);
}

t_data	del_extra_spaces(t_data data)
{
	int		i;
	int		j;
	int		var;
	char	*strcpy;

	i = 0;
	j = 0;
	data.input = ft_strdup(data.terminal_input);
	if (data.input)
		strcpy = ft_calloc(sizeof(char), ft_strlen(data.input) + 1);
	if (data.input == NULL)
		return (data);
	while (data.input[i] == ' ')
		i++;
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39 || data.input[i] == 34)
		{
			var = i;
			i = skip_quotes(data.input, i);
			while (var < (i))
			{
				strcpy[j] = data.input[var];
				var++;
				j++;
			}
		}
		while (data.input[i] == ' ' && (data.input[i + 1] == ' ' || data.input[i
				+ 1] == '\0' || data.input[i + 1] == '|' || data.input[i
				+ 1] == '<' || data.input[i + 1] == '>'))
			i++;
		if (data.input[i] == '|' || data.input[i] == '<'
			|| data.input[i] == '>')
		{
			if ((data.input[i] == '<' && data.input[i + 1] == '>')
				|| (data.input[i] == '>' && data.input[i + 1] == '<'))
			{
				data.error = true;
				printf("syntax error near unexpected token '%c\n", data.input[i
					+ 1]);
			}
			while (data.input[i] == '|' || data.input[i] == '<'
				|| data.input[i] == '>')
			{
				strcpy[j] = data.input[i];
				i++;
				j++;
			}
			while (data.input[i] == ' ')
				i++;
		}
		if (data.input[i] == '\0')
			break ;
		strcpy[j] = data.input[i];
		i++;
		j++;
	}
	free(data.input);
	data.input = strcpy;
	return (data);
}

t_data	split_input(t_data data, t_variables var)
{
	int	i;

	i = 0;
	while (data.input[var.i] != '\0')
	{
		if (data.input[var.i] == 39 || data.input[var.i] == 34)
			var.i = skip_quotes(data.input, var.i) + 1;
		if (data.input[var.i] == '|')
			data.nbr_cmd++;
		var.i++;
	}
	// printf("nbr_cmd = %d\n", data.nbr_cmd);
	data.fds = (int **)malloc(sizeof(int *) * data.nbr_cmd);
	while (var.n < data.nbr_cmd)
	{
		data.fds[var.n] = (int *)malloc(sizeof(int) * 2);
		data.fds[var.n][0] = 0; // lekkano
		data.fds[var.n][1] = 1; // non so perchè
		var.n++;
	}
	var.n = 0;
	var.i = 0;
	if (data.input)
		data.cube_input = cube_alloc(data.input, data.nbr_cmd);
	while (data.input[var.i] != '\0')
	{
		if (data.input[var.i] == '<')
		{
			data = redirection_handle(data, var.i, 1, var.n);
		}
		else if (data.input[var.i] == '>')
		{
			data = redirection_handle(data, var.i, 0, var.n);
		}
		if (data.input[var.i] == 39 || data.input[var.i] == 34)
		{
			i = var.i;
			var.i = skip_quotes(data.input, var.i) + 1;
			if (data.input[var.i] == '\0')
				break ;
			while (var.i > i)
			{
				data.cube_input[var.n][var.k][var.j] = data.input[i];
				i++;
				var.j++;
			}
		}
		else if (data.input[var.i] == '|')
		{
			data.cube_input[var.n][var.k][var.j] = '\0';
			var.n++;
			var.k = 0;
			var.j = 0;
			var.i++;
			while (data.input[var.i] == ' ')
				var.i++;
		}
		else if (data.input[var.i] == ' ')
		{
			data.cube_input[var.n][var.k][var.j] = '\0';
			var.j = 0;
			var.k++;
			var.i++;
		}
		else
		{
			data.cube_input[var.n][var.k][var.j] = data.input[var.i];
			var.i++;
			var.j++;
		}
	}
	return (data);
}

t_data	redirection_handle(t_data data, int j, bool io, int n)
{
	int		i;
	char	*strcpy;

	i = 0;
	while (data.input[j + i] != '<' && data.input[j + i] != '\0' && data.input[j + i] != '>' && data.input[j + i] != '|')
		i++;
	strcpy = ft_substr(data.input, j + 1, i + j);
	if (io == 0)
	{
		data.fds[n][0] = open(strcpy, O_WRONLY | O_CREAT, 0644);
		if (data.fds[n][0] == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strerror(errno), 2); ///da testare
			ft_putstr_fd("\n", 2);
			data.error = true;
		}
	}
	else
	{
		data.fds[n][1] = open(strcpy, O_RDONLY);
		if (data.fds[n][1] == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			data.error = true;
		}
	}
	return (data);
}

char	***cube_alloc(char *str, int nbr_cmd)
{
	int		i;
	int		j;
	int		k;
	int		n;
	char	***cube;

	i = 0;
	j = 0;
	k = 0;
	n = 0;
	cube = ft_calloc(nbr_cmd + 1, sizeof(char **));
	while (i < nbr_cmd)
	{
		while (str[n] != '|' && str[n] != '\0')
		{
			if (str[n] == 39)
			{
				n++;
				while (str[n] != 39 && str[n] != '\0')
					n++;
				if (str[n] == '\0')
					break ;
			}
			if (str[n] == 34)
			{
				n++;
				while (str[n] != 34 && str[n] != '\0')
					n++;
				if (str[n] == '\0')
					break ;
			}
			if (str[n] == ' ')
				k++;
			n++;
		}
		cube[i] = ft_calloc(k + 2, sizeof(char *));
		while (j <= k)
		{
			cube[i][j] = ft_calloc(n + 1, sizeof(char));
			j++;
		}
		n++;
		i++;
		j = 0;
		k = 0;
	}
	return (cube);
}
