/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:13:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 15:24:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE 2056
# define KEY_UP 4283163
# define KEY_DOWN 4348699 
# define KEY_RIGHT 4414235
# define KEY_LEFT 4479771

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
void	ft_file_to_string();
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
char	*find_aliases(char *line);
void	ft_new_alias(char **new_values);
int		ft_put_alias_errors(char **str);
void	ft_get_location_info(char **path, char **git);
void	ft_replace_content(t_arg *info, int put);
int		ft_check_input_for_ctrl_keys(t_arg **new, int buf, t_arg *first);
int		ft_check_special_input(t_arg **new, int buf, t_arg **first_arg);
t_arg	*new_arg();
void	ft_listdel(t_arg **first);

# include <unistd.h>

#endif 
