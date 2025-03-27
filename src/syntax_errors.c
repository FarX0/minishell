/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:22:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/27 10:54:14 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_jumped_spaces(char *str, int *i)
{
	int	jumped;

	(*i)++;
	jumped = 0;
	while (str[*i] == ' ')
	{
		(*i)++;
		jumped++;
	}
	(*i)--;
	return (jumped);
}

int	check_after_spaces(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
			ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n",
				2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n",
				2);
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
			ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n",
				2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `<'\n",
				2);
	}
	else if (str[*i] == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (str[*i] == '\0')
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else
		return (false);
	return (true);
}

static void	print_redirection_error(char *str, int i, char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token == '\0')
		write(2, "newline", 7);
	else
	{
		write(2, &token, 1);
		if (str[i + 2] && ((token == str[i] && str[i + 2] == str[i])
				|| (token != str[i] && str[i + 2] == token)))
			write(2, &str[i + 2], 1);
	}
	ft_putstr_fd("'\n", 2);
}

static bool	check_double_red_syntax(char *str, int i, int red, int rev)
{
	if (str[i + 2] == '|' || str[i + 2] == '\0' || str[i + 2] == rev || str[i
		+ 2] == red)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (str[i + 2] == '\0')
			write(2, "newline", 7);
		else
		{
			write(2, &str[i + 2], 1);
			if ((str[i + 3]) && (((str[i + 2] == rev) && (str[i + 3] == rev))
					|| ((str[i + 2] == red) && (str[i + 3] == red)) || ((str[i
							+ 2] == '|'))))
				write(2, &str[i + 3], 1);
		}
		ft_putstr_fd("'\n", 2);
		return (true);
	}
	return (false);
}

bool	redirection_syntax(int red, int i, char *str)
{
	int	rev;

	rev = 60;
	if (red == 60)
		rev += 2;
	if (has_jumped_spaces(str, &i))
		if (check_after_spaces(str, &i))
			return (true);
	if (str[i + 1] == rev || str[i + 1] == '|' || str[i + 1] == '\0')
	{
		print_redirection_error(str, i, str[i + 1]);
		return (true);
	}
	else if (str[i + 1] == red)
		return (check_double_red_syntax(str, i, red, rev));
	return (false);
}

static bool	handle_pipe_syntax(char *str, int *i)
{
	has_jumped_spaces(str, i);
	if (!str[*i + 1] || str[*i + 1] == '|' || str[*i + 1] == '>' || str[*i
		+ 1] == '<' || str[*i + 1] == '\0')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (str[*i + 1] == '\0')
			write(2, "newline", 7);
		else
			write(2, &str[*i + 1], 1);
		if (str[*i + 1] && str[*i + 2] && ((str[*i + 1] == '<' && str[*i
					+ 2] == '<') || (str[*i + 1] == '>' && str[*i + 2] == '>')))
			write(2, &str[*i + 2], 1);
		ft_putstr_fd("'\n", 2);
		return (true);
	}
	return (false);
}

static void	handle_quotes(char *str, int *i)
{
	skip_quotes(str, *i);
	(*i)--; // to compensate the i++ in the loop
}

bool	syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			handle_quotes(str, &i);
		}
		else if (str[i] == '|')
		{
			if (handle_pipe_syntax(str, &i))
				return (true);
		}
		else if (str[i] == '<')
		{
			if (redirection_syntax(60, i, str) == true)
				return (true);
		}
		else if (str[i] == '>')
			if (redirection_syntax(62, i, str) == true)
				return (true);
		i++;
	}
	return (false);
}
