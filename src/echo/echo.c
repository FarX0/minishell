/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/01/24 17:00:44 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(t_data* data, char** args)
{
	int	i;
	int	n;

	(void)data;
	i = 0;
	int aug = 1; // numero argomenti in modo che ogni ciclo prende un argomrnto
	if (args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	/* while(args[aug])
		aug++;
	aug = 1;*/
	while (args[aug])

	{
		if (args[aug][i] && strcmp(&args[aug][i],"-n") == 0) //-n
			i++;
		while (args[aug][i])
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
	printf("\n");
	return (0);
}
