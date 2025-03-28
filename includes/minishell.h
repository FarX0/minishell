/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:01:24 by tfalchi           #+#    #+#             */
/*   Updated: 2025/03/28 17:15:44 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/ioctl.h>

typedef struct s_data
{
	int		original_input;
	int		original_output;
	int		nbr_cmd;
	int		exit_code;
	int		**fds; // [0,4] [3,1] dup2(fds[0][1], 1) -> 4 -> 1  close(fds[0][1])
	char	**env;
	char	*terminal_input;
	char	*input;
	char	***cube_input;
	char	*path;
	char	**aug;
	bool	error;
	int		l_pid;
}			t_data;

typedef struct s_variables
{
	int		i;
	int		j;
	int		k;
	int		n;
}			t_variables;

// STUFF
int			ft_mtxlen(char **matrix);

//------------------------------------

//syntax_errors.c
bool		syntax_error(char *str);

// execute_command.c
int 		execute_command(t_data* data, int cmd_idx, char*** args);
int 		builtin_env(char** matrix);

// initialize_data.c
t_data		initialize_data(char **env);
char		**matrix_dup(char **matrix);

// free_and_null.c
void		free_all(t_data *data);
void		free_input(t_data *data);
void		free_env(t_data *data);
void		free_matrix(char **matrix);

// cd.c
int builtin_cd(t_data* data, char** args);
char		*get_env_value(char **env, char *key);

// pwd.c
int			pwd(void);

// echo.c
int builtin_echo(char** args);

// parsing.c
t_data		parsing(t_data data, t_variables var);
t_data		del_extra_spaces(t_data data);
t_data		split_input(t_data data, t_variables var);
char		***cube_alloc(char *str, int nbr_cmd);
t_data		redirection_handle(t_data data, int j, bool io, int n);

// export.c
int 		export(t_data* data, char** args);
void		env_modification(t_data* data, int j, int x, char** args);

// export_utils.c
void		print_export(t_data data);
char		**realloc_env(t_data data);
char		**sort_env(t_data data);
char		**mat_command(t_data *data, int index);

// utils.c
char		*till_redirection(char *str);
char		*find_and_replace(char *str_og, char *new, int start, int ignore);
char		*remove_quotes(char *str);
bool		is_builtin(char *cmd);

// char		*dollar_red(char *str, t_data *data);
int			is_executable(char *path);
void		handle_relative_path(t_data *data);

// utils2.c
int			skip_quotes(char *str, int i);
t_data		arrays_fds(t_data data);
void		print_matrix(char **matrix);

// utils_matrix.c
int			same_name(char *envp, char *to_find);
int			find_in_env(char **envp, char *to_find);
char		*dollar_expansion(t_data data);

// unset.c
int builtin_unset(t_data* data, char** args);
char** env_dup(char** matrix, t_data* data, char** args);
int			longest_string(char *str1, char *str2);

// pipex.c
void		pipex(t_data *data, int i, int fd_in, int fd_out);

// operators.c
void		handle_here_doc(t_data *data, int i);
void		execve_command(t_data *data);

// exit.c
void builtin_exit(t_data* data, char** args);

// here_doc.c
int			heredoc(t_data *data, char *limiter);
void		ft_sigdoc(int sig);
int get_file_name(char *str, int j);

void		sigint(int sig);
extern int	g_lobal;

void put_str_fd(char *str, int fd);

#endif
