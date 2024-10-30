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

t_data parsing(t_data data) // funzione per pulizia codice. prende data e restituisce data
{
    data = del_extra_spaces(data);
    data = split_input(data);
    return (data);
}

t_data del_extra_spaces(t_data data) // cancella spazi: prima della prima parola, dopo l'ultima e quelli in più prende data e restituisce data
{
    int i;
    int j;
    char *strcpy;
    int flag1;
    int flag2;

    flag1 = 0;
    flag2 = 0;
    i = 0;
    j = 0;
    data.input = ft_strdup(data.original_input);
    if (data.input)
        strcpy = ft_calloc(sizeof(char), ft_strlen(data.input) + 1);
    while (data.input[i] == ' ')
        i++;
    while (data.input[i] != '\0')
    {
        if (data.input[i] == 39 && flag1 % 2 == 0)
            flag2 += 1;
        if (data.input[i] == 34 && flag2 % 2 == 0)
            flag1 += 1;
        while (data.input[i] == ' ' && data.input[i + 1] == ' ' && flag1 % 2 == 0 && flag2 % 2 == 0)
            i++;
        if (data.input[i] == ' ' && flag1 % 2 == 0 && flag2 % 2 == 0 && data.input[i + 1] == '\0')
            i++;
        strcpy[j] = data.input[i];
        i++;
        j++;
    }
    strcpy[j] = '\0';
    data.input = strcpy;
    return (data);
}

t_data split_input(t_data data) // split dell'input in un array di stringhe. prende data e restituisce data
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    if (data.input)
        data.matrix_input = matrix_alloc(data.input);
    else
        return (data);
    while (data.input[i] != '\0')
    {
        if (data.input[i] == 39)
        {
            i++;
            while (data.input[i] != 39 && data.input[i] != '\0')
            {
                data.matrix_input[k][j] = data.input[i];
                i++;
                j++;
            }
            if (data.input[i] == 39)
                i++;
        }
        else if (data.input[i] == 34)
        {
            i++;
            while (data.input[i] != 34 && data.input[i] != '\0')
            {
                data.matrix_input[k][j] = data.input[i];
                i++;
                j++;
            }
            if (data.input[i] == 34)
                i++;
        }
        else if (data.input[i] == ' ')
        {
            if (j != 0)
            {
                data.matrix_input[k][j] = '\0';
                j = 0;
                k++;
            }
            i++;
        }
        else
        {
            data.matrix_input[k][j] = data.input[i];
            i++;
            j++;
        }
    }
    if (j > 0) // Termina l'ultima stringa se non vuota
        data.matrix_input[k][j] = '\0';
    return (data);
}

char **matrix_alloc(char *str)
{
    int i;
    int j;
    int k;
    char **matrix;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
        {
            i++;
            while (str[i] != 39 && str[i] != '\0')
                i++;
        }
        else if (str[i] == 34)
        {
            i++;
            while (str[i] != 34 && str[i] != '\0')
                i++;
        }
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
            if (str[i] == 39)
            {
                i++;
                while (str[i] != 39 && str[i] != '\0')
                    i++;
            }
            else if (str[i] == 34)
            {
                i++;
                while (str[i] != 34 && str[i] != '\0')
                    i++;
            }
            i++;
            j++;
        }
        matrix[k] = ft_calloc(sizeof(char), j + 1);
        k++;
        j = 0;
        i++;
    }
    matrix[k] = NULL;//da provare a togliere in norminette
    return (matrix);
}
