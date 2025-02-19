/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2025/01/20 17:41:40 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atolli(const char *nptr);

void builtin_exit(t_data* data, char** args)
{
	long long int	exit_code;
	int				sign;
	char			*arg;

	sign = 1;
	if (args[1])
	{
		arg = ft_strdup(args[1]);
		if (args[1][0] == '-')
		{
			sign = -1;
			arg++;
		}
		exit_code = ft_atolli(arg);
		free(arg);
		if (exit_code == 0 && args[1][0] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n",
				args[1]);
			exit_code = 2;
		}
		else if (args[2])
		{
			ft_printf("exit: too many arguments\n");
			data->exit_code = 1;

			return ;
		}
	}
	else
		exit_code = 0;
	ft_printf("exit\n");
	free_all(data);
	if (sign == -1)
	{
		exit_code = exit_code - 256;
		exit_code = exit_code * -1;
	}
	exit(exit_code);
}

long long int	ft_atolli(const char *nptr)
{
	long long int	res;
	int				i;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
	{
		sign = 1;
		i++;
	}
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
