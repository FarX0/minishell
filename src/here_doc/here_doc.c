/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:22:43 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/27 18:29:07 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_lobal;

int	get_file_name(char *str, int j);

void	ft_sigdoc(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_lobal = 130;
	(void)sig;
}

int	heredoc(t_data *data, char *limiter)
{
	int		fd;
	char	*line;

	printf("limiter: %s\n", limiter);
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		data->error = true;
		return (-1);
	}
	signal(SIGINT, ft_sigdoc);
	while (true)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (g_lobal == 130)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	signal(SIGINT, sigint);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}

int	get_file_name(char *str, int j)
{
	int	start;

	start = j;
	while (str[j] != ' ' && str[j] != '\0' && str[j] != '|')
	{
		if (str[j] == 39 || str[j] == 34)
		{
			j = skip_quotes(str, j);
			j--;
		}
		j++;
	}
	return (j - start);
}
