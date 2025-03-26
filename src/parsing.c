/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2025/02/27 10:15:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data parsing(t_data data, t_variables var)
{
	data = del_extra_spaces(data);
	if (data.error == true)
		return (data);
	data = split_input(data, var);
	return (data);
}

t_data del_extra_spaces(t_data data)
{
	int i;
	int j;
	int var;
	char *str;

	i = 0;
	j = 0;
	data.input = ft_strdup(data.terminal_input);
	if (data.input == NULL)
		return (data);
	str = ft_calloc(sizeof(char *), ft_strlen(data.input) + 1);
	while (data.input[i] == ' ')
		i++;
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39 || data.input[i] == 34)
		{
			var = i;
			i = skip_quotes(data.input, i);
			if (i == -1)
			{
				data.error = true;
				perror("Minishell: Quote not closed");
				free(str);
				return (data);
			}
			while (var < (i))
			{
				str[j] = data.input[var];
				var++;
				j++;
			}
		}
		while (data.input[i] == ' ' && (data.input[i + 1] == ' ' || data.input[i + 1] == '\0' || data.input[i + 1] == '|' || data.input[i + 1] == '<' || data.input[i + 1] == '>'))
			i++;
		if (data.input[i] == '|' || data.input[i] == '<' || data.input[i] == '>')
		{
			if (syntax_error(data.input) == true)
			{
				data.error = true;
				free(str);
				return (data);
			}
			while (data.input[i] == '|' || data.input[i] == '<' || data.input[i] == '>')
			{
				str[j] = data.input[i];
				i++;
				j++;
			}
			while (data.input[i] == ' ')
				i++;
			continue;
		}
		if (data.input[i] == '\0')
			break;
		str[j] = data.input[i];
		i++;
		j++;
	}
	free(data.input);
	data.input = str;
	return (data);
}

t_data split_input(t_data data, t_variables var)
{
	int i;
	while (data.input[var.i] != '\0')
	{
		if (data.input[var.i] == 39)
		{
			var.i = skip_quotes(data.input, var.i);
			continue;
		}
		if (data.input[var.i] == 34)
		{
			while (var.i > 0 && data.input[var.i - 1] == ' ')
				var.i--;
			if (var.i > 0 && strncmp(&data.input[var.i - 1], "<<", 2) == 0)
			{
				while (data.input[var.i] != 34 && data.input[var.i] != '\0')
					var.i++;
				var.i++;
				while (data.input[var.i] != 34 && data.input[var.i] != '\0')
					var.i++;
				var.i++;
			}
			else
			{
				while (data.input[var.i] != 34 && data.input[var.i] != '\0')
					var.i++;
				var.i++;
				while (data.input[var.i] != 34 && data.input[var.i] != '\0')
				{
					if (data.input[var.i] == '$')
					{
						data.input = dollar_expansion(data);
						if (data.error == true)
							return (data);
						var.i = 0;
					}
					else
						var.i++;
				}
				if (data.input[var.i] != '\0')
					var.i++;
			}
			continue;
		}
		if (data.input[var.i] == '|')
			data.nbr_cmd++;
		if (data.input[var.i] == '$')
		{
			while (var.i > 1 && data.input[var.i - 1] && data.input[var.i - 1] == ' ' && var.i - 2 >= 0)
				var.i--;
			if (var.i > 0 && ft_strncmp(&data.input[var.i - 1], "<<", 2) == 0)
			{
				while (data.input[var.i] != '$' && data.input[var.i] != '\0')
					var.i++;
				var.i++;
				while (data.input[var.i] != ' ' && data.input[var.i] != '\0')
					var.i++;
				if (data.input[var.i] != '\0') //
					var.i++;
			}
			else
			{
				while (data.input[var.i] != '$' && data.input[var.i] != '\0')
					var.i++;
				if (data.input[var.i] == '$')
				{
					if(var.i >= 2)
					{
						if(data.input[var.i - 1] == '<' && data.input[var.i - 2] == '<')
						{
							while (data.input[var.i] != ' ' && data.input[var.i] != '\0')
								var.i++;
							if (data.input[var.i] != '\0')
								var.i++;
						}
						else
						{
							data.input = dollar_expansion(data);
						}
						if (data.input[var.i] == '$')
							var.i++;
					}
					else
					{
						data.input = dollar_expansion(data);
						if (data.input[var.i] == '$')
							var.i++;
					}	
				}
			}
			continue;
		}
		var.i++;
	}
	data.fds = (int **)malloc(sizeof(int *) * (data.nbr_cmd + 1));
	if (!data.fds)
	{
		data.error = true;
		return (data);
	}
	while (var.n < data.nbr_cmd)
	{
		data.fds[var.n] = (int *)malloc(sizeof(int) * 2);
		if (!data.fds[var.n])
		{
			data.error = true;
			return (data);
		}
		var.n++;
	}
	data = arrays_fds(data);
	var.n = 0;
	data.fds[data.nbr_cmd] = NULL;
	var.n = 0;
	var.i = 0;
	if (data.input)
		data.cube_input = cube_alloc(data.input, data.nbr_cmd);
	while (data.input[var.i] != '\0')
	{
		// controllase sei in "" o '' :)
		if (data.input[var.i] == '<')
		{
			data = redirection_handle(data, var.i, 1, var.n);
			data.cube_input[var.n][var.k][var.j++] = data.input[var.i++];
			if (data.input[var.i] == '<')
				data.cube_input[var.n][var.k][var.j++] = data.input[var.i++];
		}
		else if (data.input[var.i] == '>')
		{
			data = redirection_handle(data, var.i, 0, var.n);
			data.cube_input[var.n][var.k][var.j++] = data.input[var.i++];
			if (data.input[var.i] == '>')
				data.cube_input[var.n][var.k][var.j++] = data.input[var.i++];
		}
		else if (data.input[var.i] == 39 || data.input[var.i] == 34)
		{
			i = var.i;
			var.i = skip_quotes(data.input, var.i);
			/* if (data.input[var.i] == '\0')
				break ; */
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
			data.cube_input[var.n][var.k][var.j++] = data.input[var.i++];
	}
	return (data);
}

t_data redirection_handle(t_data data, int j, bool io, int n)
{
	int i;
	char *fiel;

	// while (data.input[j + i] != '<' && data.input[j + i] != '>' && data.input[j + i] != '|')
	//  	i++;
	// io = 0 && i = 0 -> >>
	// io = 0 && i = 1 -> >
	// io = 1 && i = 0 -> <<
	// io = 1 && i = 1 -> <
	if (io == 0)
	{
		if (data.input[j + 1] && data.input[j + 1] == '>')
			i = 0;
		else
			i = 1;
	}
	else
	{
		if (data.input[j + 1] && data.input[j + 1] == '<')
			i = 0;
		else
			i = 1;
	}
	if (data.input[j + 1] == '<' || data.input[j + 1] == '>')
		j++;
	fiel = remove_quotes(ft_substr(data.input, j + 1, get_file_name(data.input, j + 1)));
	if (io == 0)
	{
		if (data.fds[n][1] != 1)
			close(data.fds[n][1]);
		if (i == 1)
		{
			data.fds[n][1] = open(fiel, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data.fds[n][1] == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2); /// da testare
				ft_putstr_fd("\n", 2);
				data.error = true;
			}
		}
		else
		{
			data.fds[n][1] = open(fiel, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data.fds[n][1] == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2); /// da testare
				ft_putstr_fd("\n", 2);
				data.error = true;
			}
		}
	}
	else
	{
		if (data.fds[n][0] != 0)
			close(data.fds[n][0]);
		if (i == 1)
		{
			data.fds[n][0] = open(fiel, O_RDONLY, 0644);
			if (data.fds[n][1] == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				data.error = true;
			}
		}
		else
		{
			data.fds[n][0] = heredoc(&data, fiel);
			j = j + 2;
			while (data.input[j] != '\0' && data.input[j] != '|' && data.input[j] != '<' && data.input[j] != '>')
				j++;//possibile rimuovere queste 3 righe?
		}
	}
	free(fiel);
	return (data);
}

char ***cube_alloc(char *str, int nbr_cmd)
{
	int i;
	int j;
	int k;
	int n;
	char ***cube;

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
					break;
			}
			if (str[n] == 34)
			{
				n++;
				while (str[n] != 34 && str[n] != '\0')
					n++;
				if (str[n] == '\0')
					break;
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
		cube[i][k + 1] = NULL;
		n = 0;
		i++;
		j = 0;
		k = 0;
	}
	cube[nbr_cmd] = NULL;
	return (cube);
}
