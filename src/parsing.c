/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/10 12:46:57 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data parsing(t_data data) //funzione per pulizia codice. prende data e restituisce data
{
	data = del_extra_spaces(data);
	data = split_input(data);
	return (data);
}

t_data del_extra_spaces(t_data data)//cancella spazi: prima della prima parola, dopo l'ultima e quelli in più prende data e restituisce data
{
	int i;
	int j;
	char *strcpy;

	i = 0;
	j = 0;
	data.input = ft_strdup(data.original_input);
	if (data.input)
		strcpy = ft_calloc(sizeof(char), ft_strlen(data.input) + 1);
	while (data.input[i] == ' ')
		i++;
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39 && data.flag1 % 2 == 0)
			data.flag2 += 1;
		if (data.input[i] == 34 && data.flag2 % 2 == 0)
			data.flag1 += 1; 
		while (data.input[i] == ' ' && data.input[i + 1] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0)
			i++;
		if (data.input[i] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0 && data.input[i + 1] == '\0')
			i++;
		strcpy[j] = data.input[i];
		i++;
		j++;
	}
	data.input = strcpy;
	//free(strcpy)
	return (data);
}

t_data split_input(t_data data) //split dell'input in un array di stringhe. prende data e restituisce data
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (data.input)
		data.matrix_input = matrix_alloc(data.input, data.flag1, data.flag2);
	while (data.input[i] != '\0')
	{
		if (data.input[i] == 39) //da fare on un &
		{
			i++;
			while (data.input[i] != 39 && data.input[i] != '\0')
			{
				data.matrix_input[k][j] = data.input[i];
				i++;
				k++;
			}
			if(data.input[i] == 39)
				i++;
		}
		if (data.input[i] == 34)
		{
			i++;
			while (data.input[i] != 34 && data.input[i] != '\0')
			{
				data.matrix_input[k][j] = data.input[i];
				i++;
				k++;
			}
			if(data.input[i] == 34)
				i++;
		}
		if (data.input[i] == ' ')//fattibile con split
		{
			data.matrix_input[k][j] = '\0';
			j = 0;
			k++;
			i++;
		}
		if (data.input[i] == '\0')
				break;
		data.matrix_input[k][j] = data.input[i];
		i++;
		j++;
	}
	return (data);
}

char **matrix_alloc(char *str, int flag1, int flag2)
{
	int i; 
	int j;
	int k;
	int flag;
	char **matrix;

	i = 0;
	j = 0;
	k = 0;
	if (flag1 % 2 == 1 || flag2 % 2 == 1)
		flag = 1;
	(void)flag;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	matrix = ft_calloc(sizeof(char *), k + 2);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] != ' ' && str[i] != '\0')
		{
			i++;
			j++;
		}
		matrix[k] = ft_calloc(sizeof(char), j + 1);
		k++;
		j = 0;
		if (str[i] == '\0')
			break;
		i++;
	}
	return (matrix);
}
