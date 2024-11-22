/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:39:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/18 16:01:15 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_realloc(char *str, int size)
{
    char *new_str;

    new_str = ft_calloc(sizeof(char), size);
    ft_strlcpy(new_str, str, size);
    free(str);
    return (new_str);
}