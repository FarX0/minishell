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

int get_file_name(char *str, int j);

int g_lobal;

void	ft_sigdoc(int sig)
{
	write(0, "\0", 1);
	g_lobal= 130;
	(void)sig;
}

int	heredoc(t_data *data, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		data->error = true;
		return (-1);
	}
	printf("limiter = |%s|\n", limiter);
	signal(SIGINT, ft_sigdoc);
	while (true)
	{
		line = readline("heredoc>");
		if (line == NULL)
			break ;
		printf("line = |%s|\n", line);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			write(fd, "\n", 1);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	signal(SIGINT, sigint);
	return (fd);
}


int get_file_name(char *str, int j)
{
	int		i;

	i = 0;
	while (str[j + i] != ' ' && str[j + i] != '\0' && str[j + i] != '|')
	{
		if (str[j + i] == 39 || str[j + i] == 34)
			i = skip_quotes(str, j + i);
		i++;
	}
	return (i);
}

