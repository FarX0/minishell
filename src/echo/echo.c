/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/28 10:45:45 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int aug = 1; numero argomenti in modo che ogni ciclo prende un argomento
int	builtin_echo(t_data *data, char **args)
{
	int	i;
	int	n;
	int	aug;
	int	flag;

	flag = 0;
	(void)data;
	i = 0;
	aug = 1;
	if (args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (args[aug] && args[aug][i] && args[aug][i + 1]
		&& ft_strncmp(&args[aug][i], "-n", 2) == 0)
	{
		i++;
		while (args[aug][i] && args[aug][i] == 'n')
			i++;
		if (args[aug][i] == '\0')
		{
			flag = 1;
			aug++;
			i = 0;
		}
		else
		{
			i = 0;
			break;
		}
	}
	while (args[aug])
	{
		while (args[aug] && args[aug][i])
		{
			if (args[aug][i] == '\"' || args[aug][i] == '\'')
			{
				n = i + 1;
				i = skip_quotes(args[aug], i);
				while (n < i - 1)
				{
					printf("%c", args[aug][n]);
					n++;
				}
			}
			else
			{
				printf("%c", args[aug][i]);
				i++;
			}
		}
		i = 0;
		if (args[aug + 1] != NULL && args[aug][0] != '\0')
			printf(" ");
		aug++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
