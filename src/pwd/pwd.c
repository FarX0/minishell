/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:08:51 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/07 12:18:38 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd()
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