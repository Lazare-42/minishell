/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:13:02 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 06:54:56 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE 2056
# define KEY_UP 4283163
# define RESET_HISTORIC 400
# define KEY_RIGHT 300
# define KEY_LEFT 200
# define HISTORIC 100

# include "../libft/include/libft.h"

typedef struct 		s_arg
{
	char			*arg;
	char			*line_right;
	char			*old_line;
	struct 	s_arg	*next;
	struct	s_arg	*previous;
}					t_arg;

int		ft_recognize_builtin_command(char *str);
void	ft_put_command_errors(char *str);
char	**ft_find_prog_path(char *arg, char **environ);
char	*ft_find_my_prog_path(char *arg);
void	ft_change_dir(char *str);
int		ft_file_to_string(t_arg *first);
void	ft_echo(char **str);
void	ft_put_env();
void	ft_sort_setenv(char **args);
char	**ft_setenv(char **name, int new_environ_size, char **environ_tocpy);
t_arg	*ft_store_args(t_arg *first, t_arg *new_arg);
void		ft_launch_processes(char **arguments, t_arg **first,
		char **new_env);
void	ft_complete_command(int quote_type, char **command_line, t_arg **first);
int		ft_check_commas(char *str);
void	ft_recognize_processes(char *str, t_arg **first);
char	**ft_split_whitespaces_not_quotes(char *str);
char	*ft_advance_string_for_quote(char *str);
void	ft_unsetenv(char **str);
void	ft_env(char **args, t_arg **first);
int		ft_new_environ_size(char **args, char **environ_tocpy);
int		ft_look_inside(char *line, t_arg **first);
void	ft_advance_lst_to(t_arg *first, t_arg *new, t_arg ** to_find,
		int dir_up);
void	ft_get_location_info(char **path, char **git);
int		operate_special_input(t_arg **new, char *buf, t_arg **first, int fd);
t_arg	*new_arg();
void	ft_listdel(t_arg **first);
int		get_terminal_description(void);
void	ft_print_current_directory(void);
int		put_fatal_error(char *str);
void	put_error(char *str);
void	get_cursor_position(int *x, int *y, int fd);
int		window_info(int info_request);
void	print_handler(char *c, int print, int fd); 

#endif 
