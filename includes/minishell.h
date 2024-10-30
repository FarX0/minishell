/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:01:24 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/10 15:38:12 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	char	**env;				
	char	*original_input;
	char	*input;
	char	**matrix_input;
}			t_data;

//execute_command.c
void	execute_command(t_data *data);
void	print_matrix(char **matrix);

//initialize_data.c
t_data	initialize_data(char **env);
char	**matrix_dup(char **matrix);

//free_and_null.c
void	free_all(t_data *data);
void	free_input(t_data *data);
void	free_env(t_data *data);

//pwd.c
int 	pwd();

//echo.c
void builtin_echo(t_data *data);

//parsing.c
t_data	parsing(t_data data);
t_data	del_extra_spaces(t_data data);
t_data	split_input(t_data data);
char	**matrix_alloc(char *str);

//export.c
void	export(t_data *data);
void	env_modification(t_data *data, int j);

//export_utils.c
void	print_export(t_data data);
char	**realloc_env(t_data data);
char	**sort_env(t_data data);

//utiils.c
char	*ft_realloc(char *str, int size);

#endif
