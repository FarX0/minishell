/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:19 by tfalchi           #+#    #+#             */
/*   Updated: 2024/11/19 16:56:13 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to parse input and split on pipes, redirections
t_data parsing(t_data data)
{
    data = del_extra_spaces(data);  // Remove extra spaces
    data = split_input(data);  // Split input by pipes and redirections
    return (data);
}

// Function to remove unnecessary spaces outside of quotes
t_data del_extra_spaces(t_data data)
{
    int i = 0;
    int j = 0;
    char *strcpy;

    data.input = ft_strdup(data.original_input);
    if (data.input)
        strcpy = ft_calloc(sizeof(char), ft_strlen(data.input) + 1);

    while (data.input[i] == ' ')  // Skip leading spaces
        i++;

    while (data.input && data.input[i] != '\0')
    {
        // Handle single and double quotes
        if (data.input[i] == 39 && data.flag1 % 2 == 0)
            data.flag2 += 1;
        if (data.input[i] == 34 && data.flag2 % 2 == 0)
            data.flag1 += 1;

        // Skip extra spaces when not inside quotes
        while (data.input[i] == ' ' && data.input[i + 1] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0)
            i++;

        if (data.input[i] == ' ' && data.flag1 % 2 == 0 && data.flag2 % 2 == 0 && data.input[i + 1] == '\0')
            i++;

        strcpy[j++] = data.input[i++];
    }

    free(data.input);
    data.input = strcpy;

    return data;
}

// Updated to handle pipes and redirections
t_data split_input(t_data data)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int in_quotes = 0;

    if (data.input)
        data.matrix_input = matrix_alloc(data.input);
    while (data.input && data.input[i] != '\0')
    {
        // Skip spaces outside of quotes
        if (data.input[i] == 39 && in_quotes % 2 == 0) // Single quote
            in_quotes = !in_quotes;
        else if (data.input[i] == 34 && /* no % 2? */in_quotes == 0) // Double quote
            in_quotes = !in_quotes;
        /* !in_quotes? l'uno puo' chiudere l'altro */
        if ((data.input[i] == ' ' && !in_quotes) || data.input[i] == '\t') // Skip spaces
        {
            i++;
            /* continue ti fa ripartire dall'inizio del while? */
            continue;
        }
        // Handle redirection operators: <, >, <<, >>
        //da qua
        if (data.input[i] == '>' && data.input[i + 1] == '>')
        {
            data.matrix_input[k][j++] = '>';
            data.matrix_input[k][j++] = '>';
            i += 2;
        }
        else if (data.input[i] == '<' && data.input[i + 1] == '<')
        {
            data.matrix_input[k][j++] = '<';
            data.matrix_input[k][j++] = '<';
            i += 2;
        }
        else if (data.input[i] == '>' || data.input[i] == '<')
        {
            data.matrix_input[k][j++] = data.input[i++];
        }
        //a qua penso sia inutile
        else if (data.input[i] == '|')  // Pipe operator
        {
            data.matrix_input[k][j] = '\0';
            k++;
            j = 0;
            data.matrix_input[k][j++] = '|';
            i++;
        }
        else
        {
            // Regular characters, add to current argument
            data.matrix_input[k][j++] = data.input[i++];
        }

        // End current argument when space is encountered outside of quotes
        if ((data.input[i] == ' ' || data.input[i] == '\0') && !in_quotes)
        {
            data.matrix_input[k][j] = '\0';
            k++;
            j = 0;
        }
    }

    return data;
}

// Function to allocate memory for a matrix to hold the parsed input
char **matrix_alloc(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **matrix;

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
    return matrix;
}
