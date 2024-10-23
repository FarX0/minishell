/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/13 10:59:27 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *old_str, int fd)
{
	char	*buf;
	int		rd;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	rd = 1;
	while (rd > 0 && ft_strchr(old_str, '\n') == 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(old_str);
			free(buf);
			return (0);
		}
		buf[rd] = '\0';
		old_str = ft_newstrjoin(old_str, buf);
	}
	free(buf);
	return (old_str);
}

void	free_oldpeople(char **old_str)
{
	int	i;

	i = 0;
	while (i < 4096)
	{
		if (old_str[i])
		{
			free(old_str[i]);
			old_str[i] = NULL;
		}
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	*old_str[4096] = {0};
	char		*line;

	if (fd == -42)
		return (free_oldpeople(old_str), NULL);
	if (fd <= 0 && BUFFER_SIZE <= 0)
		return (0);
	old_str[fd] = ft_read(old_str[fd], fd);
	if (!old_str[fd])
		return (NULL);
	line = ft_correctline(old_str[fd]);
	old_str[fd] = ft_resto(old_str[fd]);
	if (ft_strlen(old_str[fd]) == 0)
	{
		free(old_str[fd]);
		old_str[fd] = NULL;
	}
	return (line);
}

/*
int	main(void)
{
	int		fd;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}

		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
	close(fd);
	return (0);
}*/
