/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by tfalchi           #+#    #+#             */
/*   Updated: 2024/04/10 15:05:47 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*un_s;
	unsigned char	un_c;
	size_t			i;

	un_s = (unsigned char *)s;
	un_c = (unsigned char)c;
	i = 0;
	if (!s && n == 0)
		return (NULL);
	while (i < n)
	{
		if (un_s[i] == un_c)
			return ((void *)&un_s[i]);
		i++;
	}
	return (NULL);
}
/*int main ()
{
	printf("%s",((char *)ft_memchr("qwertyuiopasdf",'p',10)));
}*/
