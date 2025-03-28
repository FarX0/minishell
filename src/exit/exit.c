/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:41:40 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/28 17:50:45 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atolli(const char *nptr);
int limit_lli(char* arg, t_data *data, char **args);

void	builtin_exit(t_data *data, char **args)
{
	long long int	exit_code;
	char			*arg;

	if (args[1])
	{
		arg = ft_strdup(args[1]);
		exit_code = limit_lli(arg, data, args);
		if (exit_code == 0 && args[1][0] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n", args[1]);
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
	exit_code = (unsigned char)exit_code;
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

int limit_lli(char* arg, t_data *data, char **args)
{
	int temp;

	if ((int)ft_strlen(arg) > (19 + (arg[0] != '-' || arg[0] != '+')))
			data->error = true;
		else if (ft_strlen(arg) == 20 && arg[0] == '+')
		{
			if (ft_strcmp(arg, "+9223372036854775807") > 0)
				data->error = true;
		}
		else if (ft_strlen(arg) == 20 && arg[0] == '-')
		{
			if (ft_strcmp(arg, "-9223372036854775808") > 0)
				data->error = true;
		}
		else if (ft_strlen(arg) == 19)
			if (ft_strcmp(arg, "9223372036854775807") > 0)
				data->error = true;
		if (args[1][0] == '-')
			arg++;
		if (data->error == true)
			return (ft_printf("exit: %s: numeric argument required\n", args[1]), free(arg), 2);
		temp = ft_atolli(arg);
		return (free(arg), temp);
}
