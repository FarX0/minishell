/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:00:36 by tfalchi           #+#    #+#             */
/*   Updated: 2025/01/25 11:53:08 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atolli(const char *nptr);

void	builtin_exit(t_data *data)
{
	long long int	exit_code;
	int				sign;
	char			*arg;
    char			*temp;
	
	arg = ft_strdup(data->cube_input[0][1]);
	sign = 1;
	if (data->cube_input[0][1])
	{
		temp = arg;
		if (data->cube_input[0][1][0] == '-')
		{
			sign = -1;
			temp++;
		}
		exit_code = ft_atolli(arg);
		if (exit_code == 0 && data->cube_input[0][1][0] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n",
				data->cube_input[0][1]);
			exit_code = 2;
		}
		else if (data->cube_input[0][2])
		{
			ft_printf("exit: too many arguments\n");
			data->exit_code = 1;
			free(arg);
			return ;
		}
	}
	else
		exit_code = 0;
	ft_printf("exit\n");
	free_all(data);
	free(arg);
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
