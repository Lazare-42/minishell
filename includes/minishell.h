/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:13:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 13:31:49 by lazrossi         ###   ########.fr       */
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
	int				line_pos;
	struct 	s_arg	*left;
	struct	s_arg	*middle;
	struct  s_arg	*right;
}					t_arg;

int		ft_recognize_builtin_command(char *str);
void	ft_put_command_errors(char *str);
void	ft_print_current_directory(void);
char	**ft_find_prog_path(char *arg, char **environ);
char	*ft_find_my_prog_path(char *arg);
int		ft_change_dir(char *str);
char	*ft_file_to_string();
void	ft_echo(char **str);
void	ft_put_env();
void	ft_sort_setenv(char **args);
char	**ft_setenv(char **name, int new_environ_size, char **environ_tocpy);
t_arg	*ft_store_args(char	*line, t_arg *first);
void	ft_launch_processes(char **arguments, char **environ_to_use);
void	ft_complete_command(int quote_type, char **command_line);
int		ft_check_commas(char *str);
void	ft_recognize_processes(char *str);
char	**ft_split_whitespaces_not_quotes(char *str);
char	*ft_advance_string_for_quote(char *str);
void	ft_unsetenv(char **str);
void	ft_env(char **args);
int		ft_new_environ_size(char **args, char **environ_tocpy);
int		ft_look_inside(char *line);
void	ft_advance_lst_to(t_arg *first, t_arg ** to_find, char **line, int line_len);
void	ft_retreat_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len);
int		set_non_canonical_input();
void	ft_clean_lst_for_line_pos(t_arg *first);

# include <unistd.h>

#endif 
