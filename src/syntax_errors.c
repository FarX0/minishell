/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:22:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/24 18:36:20 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool syntax_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] == 39)
		{
			skip_quotes(str, i);
			continue;
		}
		else if (str[i] == 34)
		{
			skip_quotes(str, i);
			continue;
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] || str[i + 1]  == '|' || str[i + 1] == '>' || str[i + 1] == '<' || str[i + 1] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if(str[i + 1] == '\0')
					write(2, "newline", 7);
				else
					write(2, &str[i + 1], 1);
				if(str[i + 2] && ((str[i + 1] == '<' && str[i + 2] == '<') || (str[i + 1] == '>' && str[i + 2] == '>')))
					write(2, &str[i + 2], 1);
				ft_putstr_fd("'\n", 2);
				return (true);
			}
		}
		else if(str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '|' || str[i + 1] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if(str[i + 1] == '\0')
					write(2, "newline", 7);
				else
				{
					write(2, &str[i + 1], 1);
					if(str[i + 2] && ((str[i + 1] == '<' && str[i + 2] == '<') || (str[i + 1] == '>' && str[i + 2] == '>')))
						write(2, &str[i + 2], 1);
				}
				ft_putstr_fd("'\n", 2);
				return (true);
			}
			else if(str[i + 1] == '<' && (str[i + 2] == '|' || str[i + 2] == '\0' || str[i + 2] == '>' || str[i + 2] == '<'))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if(str[i + 2] == '\0')
					write(2, "newline", 7);
				else
				{
					write(2, &str[i + 2], 1);
					if((str[i + 3]) && (((str[i + 2] == '>') && (str[i + 3] == '>')) || ((str[i + 2] == '<') && (str[i + 3] == '<')) || ((str[i + 2] == '|'))))
						write(2, &str[i + 3], 1);
				}
				ft_putstr_fd("'\n", 2);
				return (true);
			}
		}
		else if(str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '|' || str[i + 1] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if(str[i + 1] == '\0')
					write(2, "newline", 7);
				else
				{
					write(2, &str[i + 1], 1);
					if(str[i + 2] && (str[i + 1] == '<' && str[i + 2] == '<'))
						write(2, &str[i + 2], 1);
				}
				ft_putstr_fd("'\n", 2);
				return (true);
			}
			else if(str[i + 1] == '>' && (str[i + 2] == '|' || str[i + 2] == '\0' || str[i + 2] == '<' || str[i + 2] == '>'))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if(str[i + 2] == '\0')
					write(2, "newline", 7);
				else
				{
					write(2, &str[i + 2], 1);
					if((str[i + 3]) && (((str[i + 2] == '>') && (str[i + 3] == '>')) || ((str[i + 2] == '<') && (str[i + 3] == '<')) || ((str[i + 2] == '|'))))
						write(2, &str[i + 3], 1);
				}
				ft_putstr_fd("'\n", 2);
				return (true);
			}
		}
		i++;
	}
	return (false);
}