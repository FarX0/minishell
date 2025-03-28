/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/28 17:52:07 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_flag(int i, int aug, char **args);
void	echo_print(int aug, int i, char **args, bool flag);

int	builtin_echo(char **args)
{
	int		i;
	int		aug;
	bool	flag;

	flag = false;
	i = 0;
	aug = 1;
	if (args[1] == NULL)
		return (printf("\n"), 0);
	while (args[aug] && args[aug][i] && args[aug][i + 1]
		&& ft_strncmp(&args[aug][i], "-n", 2) == 0)
	{
		i = skip_flag(i, aug, args);
		if (args[aug][i] == '\0')
		{
			flag = true;
			aug++;
			i = 0;
		}
		else
			break ;
	}
	i = 0;
	echo_print(aug, i, args, flag);
	return (0);
}

void	echo_print(int aug, int i, char **args, bool flag)
{
	int	n;

	while (args[aug])
	{
		while (args[aug] && args[aug][i])
		{
			if (args[aug][i] == '\"' || args[aug][i] == '\'')
			{
				n = i + 1;
				i = skip_quotes(args[aug], i);
				while (n < i - 1)
					printf("%c", args[aug][n++]);
			}
			else
				printf("%c", args[aug][i++]);
		}
		i = 0;
		if (args[aug + 1] != NULL && args[aug][0] != '\0')
			printf(" ");
		aug++;
	}
	if (flag == false)
		printf("\n");
}

int	skip_flag(int i, int aug, char **args)
{
	i++;
	while (args[aug][i] && args[aug][i] == 'n')
		i++;
	return (i);
}
