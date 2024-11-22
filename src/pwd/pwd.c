/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:08:51 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/22 15:12:36 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd()
{
	char *directory = getcwd(NULL, 0);
	if (directory)
	{
		printf("%s\n", directory);
		free(directory);
		directory = NULL;
		return (0);
	}
	else
	{
		printf("Error: could not get current directory\n");
		return (1);
	}
}
