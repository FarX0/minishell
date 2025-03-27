/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/27 14:30:45 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	parsing(t_data data, t_variables var)
{
	data = del_extra_spaces(data);
	if (data.error == true)
		return (data);
	data = split_input(data, var);
	return (data);
}

bool	handle_quotes_in_cleaning(t_data *data, char *str, int *i, int *j)
{
	int	var;

	var = *i;
	*i = skip_quotes(data->input, *i);
	if (*i == -1)
	{
		data->error = true;
		perror("Minishell: Quote not closed");
		free(str);
		return (false);
	}
	while (var < (*i))
	{
		str[*j] = data->input[var];
		var++;
		(*j)++;
	}
	return (true);
}

bool	handle_special_chars(t_data *data, char *str, int *i, int *j)
{
	if (syntax_error(data->input) == true)
	{
		data->error = true;
		free(str);
		return (false);
	}
	while (data->input[*i] == '|' || data->input[*i] == '<'
		|| data->input[*i] == '>')
	{
		str[*j] = data->input[*i];
		(*i)++;
		(*j)++;
	}
	while (data->input[*i] == ' ')
		(*i)++;
	return (true);
}

bool	init_space_cleaning(t_data *data, char **str)
{
	data->input = ft_strdup(data->terminal_input);
	if (data->input == NULL)
		return (false);
	*str = ft_calloc(sizeof(char *), ft_strlen(data->input) + 1);
	if (*str == NULL)
	{
		free(data->input);
		return (false);
	}
	return (true);
}

bool	should_skip_space(char *input, int i)
{
	return (input[i] == ' ' && (input[i + 1] == ' ' || input[i + 1] == '\0'
			|| input[i + 1] == '|' || input[i + 1] == '<' || input[i
				+ 1] == '>'));
}

char	*clone(t_data data, char *str, int i, int j)
{
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39 || data.input[i] == 34)
		{
			if (!handle_quotes_in_cleaning(&data, str, &i, &j))
				return (NULL);
		}
		else if (should_skip_space(data.input, i))
			i++;
		else if (data.input[i] == '|' || data.input[i] == '<'
			|| data.input[i] == '>')
		{
			if (!handle_special_chars(&data, str, &i, &j))
				return (NULL);
			continue ;
		}
		else if (data.input[i] == '\0')
			break ;
		else
			str[j++] = data.input[i++];
	}
	str[j] = '\0';
	return (str);
}

t_data	del_extra_spaces(t_data data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!init_space_cleaning(&data, &str))
		return (data);
	while (data.input[i] == ' ')
		i++;
	str = clone(data, str, i, j);
	if (str == NULL)
		return (data);
	free(data.input);
	data.input = str;
	if (data.input == NULL)
		data.error = true;
	return (data);
}

bool	handle_heredoc_quotes(t_data *data, t_variables *var)
{
	while (var->i > 0 && data->input[var->i - 1] == ' ')
		var->i--;
	if (var->i > 0 && strncmp(&data->input[var->i - 1], "<<", 2) == 0)
	{
		while (data->input[var->i] != 34 && data->input[var->i] != '\0')
			var->i++;
		var->i++;
		while (data->input[var->i] != 34 && data->input[var->i] != '\0')
			var->i++;
		var->i++;
		return (true);
	}
	return (false);
}

bool	handle_double_quote(t_data *data, t_variables *var)
{
	if (handle_heredoc_quotes(data, var))
		return (true);
	while (data->input[var->i] != 34 && data->input[var->i] != '\0')
		var->i++;
	var->i++;
	while (data->input[var->i] != 34 && data->input[var->i] != '\0')
	{
		if (data->input[var->i] == '$')
		{
			data->input = dollar_expansion(*data);
			if (data->error == true)
				return (false);
			var->i = 0;
		}
		else
			var->i++;
	}
	if (data->input[var->i] != '\0')
		var->i++;
	return (true);
}

bool	handle_heredoc_dollar(t_data *data, t_variables *var)
{
	while (var->i > 1 && data->input[var->i - 1] && data->input[var->i
			- 1] == ' ' && var->i - 2 >= 0)
		var->i--;
	if (var->i > 0 && ft_strncmp(&data->input[var->i - 1], "<<", 2) == 0)
	{
		while (data->input[var->i] != '$' && data->input[var->i] != '\0')
			var->i++;
		var->i++;
		while (data->input[var->i] != ' ' && data->input[var->i] != '\0')
			var->i++;
		if (data->input[var->i] != '\0')
			var->i++;
		return (true);
	}
	return (false);
}

bool	check_for_heredoc(t_data *data, t_variables *var)
{
	if (var->i >= 2)
	{
		if (data->input[var->i - 1] == '<' && data->input[var->i - 2] == '<')
		{
			while (data->input[var->i] != ' ' && data->input[var->i] != '\0')
				var->i++;
			if (data->input[var->i] != '\0')
				var->i++;
			return (true);
		}
	}
	return (false);
}

bool	handle_dollar_sign(t_data *data, t_variables *var)
{
	if (handle_heredoc_dollar(data, var))
		return (true);
	while (data->input[var->i] != '$' && data->input[var->i] != '\0')
		var->i++;
	if (data->input[var->i] == '$')
	{
		if (!check_for_heredoc(data, var))
		{
			data->input = dollar_expansion(*data);
			if (data->error == true)
				return (false);
		}
		if (data->input[var->i] == '$')
			var->i++;
	}
	return (true);
}

bool	allocate_fds(t_data *data, t_variables *var)
{
	data->fds = (int **)malloc(sizeof(int *) * (data->nbr_cmd + 1));
	if (!data->fds)
	{
		data->error = true;
		return (false);
	}
	var->n = 0;
	while (var->n < data->nbr_cmd)
	{
		data->fds[var->n] = (int *)malloc(sizeof(int) * 2);
		if (!data->fds[var->n])
		{
			data->error = true;
			return (false);
		}
		var->n++;
	}
	data->fds[data->nbr_cmd] = NULL;
	return (true);
}

void	prepare_for_cube_input(t_data *data, t_variables *var)
{
	*data = arrays_fds(*data);
	var->n = 0;
	var->i = 0;
	if (data->input)
		data->cube_input = cube_alloc(data->input, data->nbr_cmd);
}

void	handle_input_redirect(t_data *data, t_variables *var)
{
	*data = redirection_handle(*data, var->i, 1, var->n);
	data->cube_input[var->n][var->k][var->j++] = data->input[var->i++];
	if (data->input[var->i] == '<')
		data->cube_input[var->n][var->k][var->j++] = data->input[var->i++];
}

void	handle_output_redirect(t_data *data, t_variables *var)
{
	*data = redirection_handle(*data, var->i, 0, var->n);
	data->cube_input[var->n][var->k][var->j++] = data->input[var->i++];
	if (data->input[var->i] == '>')
		data->cube_input[var->n][var->k][var->j++] = data->input[var->i++];
}

void	handle_quotes_in_cube(t_data *data, t_variables *var, int *i)
{
	*i = var->i;
	var->i = skip_quotes(data->input, var->i);
	while (var->i > *i)
	{
		data->cube_input[var->n][var->k][var->j] = data->input[*i];
		(*i)++;
		var->j++;
	}
}

void	handle_pipe_char(t_data *data, t_variables *var)
{
	data->cube_input[var->n][var->k][var->j] = '\0';
	var->n++;
	var->k = 0;
	var->j = 0;
	var->i++;
	while (data->input[var->i] == ' ')
		var->i++;
}

void	handle_space_char(t_data *data, t_variables *var)
{
	data->cube_input[var->n][var->k][var->j] = '\0';
	var->j = 0;
	var->k++;
	var->i++;
}

bool	process_input_for_cmds(t_data *data, t_variables *var)
{
	while (data->input[var->i] != '\0')
	{
		if (data->input[var->i] == 39)
		{
			var->i = skip_quotes(data->input, var->i);
			continue ;
		}
		if (data->input[var->i] == 34)
		{
			if (!handle_double_quote(data, var))
				return (false);
			continue ;
		}
		if (data->input[var->i] == '|')
			data->nbr_cmd++;
		if (data->input[var->i] == '$')
		{
			if (!handle_dollar_sign(data, var))
				return (false);
			continue ;
		}
		var->i++;
	}
	return (true);
}

void	build_cube_input(t_data *data, t_variables *var)
{
	int	i;

	while (data->input[var->i] != '\0')
	{
		if (data->input[var->i] == '<')
			handle_input_redirect(data, var);
		else if (data->input[var->i] == '>')
			handle_output_redirect(data, var);
		else if (data->input[var->i] == 39 || data->input[var->i] == 34)
			handle_quotes_in_cube(data, var, &i);
		else if (data->input[var->i] == '|')
			handle_pipe_char(data, var);
		else if (data->input[var->i] == ' ')
			handle_space_char(data, var);
		else
			data->cube_input[var->n][var->k][var->j++] = data->input[var->i++];
	}
}

t_data	split_input(t_data data, t_variables var)
{
	if (!process_input_for_cmds(&data, &var) || data.input == NULL)
	{
		data.error = true;
		return (data);
	}
	var.j = 0;
	var.k = 0;
	if (!process_input_for_cmds(&data, &var))
		return (data);
	if (!allocate_fds(&data, &var))
		return (data);
	prepare_for_cube_input(&data, &var);
	build_cube_input(&data, &var);
	return (data);
}

/*
	if (io == 0) Output redirection
		if (data.input[j + 1] && data.input[j + 1] == '>')
			Append mode (>>)
		else
			Truncate mode (>)
	else Input redirection
		if (data.input[j + 1] && data.input[j + 1] == '<')
			Heredoc (<<)
		else
			Regular input (<)
*/
int	determine_redirection_type(t_data data, int j, bool io)
{
	int	i;

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
	return (i);
}

// if (i == 1) Truncate mode (>)
// else Append mode (>>)
void	handle_output_redirection(t_data *data, int n, int i, char *fiel)
{
	if (data->fds[n][1] != 1)
		close(data->fds[n][1]);
	if (i == 1)
	{
		data->fds[n][1] = open(fiel, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		data->fds[n][1] = open(fiel, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (data->fds[n][1] == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		data->error = true;
	}
}

// if (i == 1) Regular input file (<)
void	handle_input_redirection(t_data *data, int n, int i, char *fiel)
{
	if (data->fds[n][0] != 0)
		close(data->fds[n][0]);
	if (i == 1)
	{
		data->fds[n][0] = open(fiel, O_RDONLY, 0644);
		if (data->fds[n][0] == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			data->error = true;
		}
	}
	else
		data->fds[n][0] = heredoc(data, fiel);
	return ;
}

// if (io == 0) => Output redirection
// else => Input redirection
t_data	redirection_handle(t_data data, int j, bool io, int n)
{
	int		i;
	char	*fiel;

	i = determine_redirection_type(data, j, io);
	if (data.input[j + 1] == '<' || data.input[j + 1] == '>')
		j++;
	fiel = remove_quotes(ft_substr(data.input, j + 1, get_file_name(data.input,
					j + 1)));
	if (io == 0)
		handle_output_redirection(&data, n, i, fiel);
	else
		handle_input_redirection(&data, n, i, fiel);
	free(fiel);
	return (data);
}

// if (str[*n] == 39) Single quote
// else if (str[*n] == 34) Double quote
int	count_fields_in_command(char *str, int *n)
{
	int	k;

	k = 0;
	while (str[*n] != '|' && str[*n] != '\0')
	{
		if (str[*n] == 39)
		{
			(*n)++;
			while (str[*n] != 39 && str[*n] != '\0')
				(*n)++;
			if (str[*n] == '\0')
				break ;
		}
		else if (str[*n] == 34)
		{
			(*n)++;
			while (str[*n] != 34 && str[*n] != '\0')
				(*n)++;
			if (str[*n] == '\0')
				break ;
		}
		if (str[(*n)++] == ' ')
			k++;
	}
	return (k);
}

void	allocate_command_fields(char ***cube, int i, int k, int n)
{
	int	j;

	j = 0;
	cube[i] = ft_calloc(k + 2, sizeof(char *));
	while (j <= k)
	{
		cube[i][j] = ft_calloc(n + 1, sizeof(char));
		j++;
	}
	cube[i][k + 1] = NULL;
}

char	***cube_alloc(char *str, int nbr_cmd)
{
	int		i;
	int		n;
	int		k;
	char	***cube;

	i = 0;
	n = 0;
	cube = ft_calloc(nbr_cmd + 1, sizeof(char **));
	while (i < nbr_cmd)
	{
		k = count_fields_in_command(str, &n);
		allocate_command_fields(cube, i, k, n);
		n = 0;
		i++;
	}
	cube[nbr_cmd] = NULL;
	return (cube);
}
