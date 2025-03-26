/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:17:40 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/25 12:11:04 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mtxlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

t_data	arrays_fds(t_data data)
{
    int i;
    int fds[2]; // Dichiarazione come array locale

    i = 0;
    while (i < data.nbr_cmd - 1)
    {
        printf("i: %d\n", i);
        pipe(fds); // Usa l'array locale
        data.fds[i][1] = fds[1];
        data.fds[i + 1][0] = fds[0];
        i++;
        printf("i2: %d\n", i);
    }
    data.fds[0][0] = 0;
    data.fds[i][1] = 1;

    return (data);
}
