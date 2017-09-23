/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 13:48:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 14:58:52 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "../libft/include/libft.h"

typedef struct 		s_arg
{
	char			*arg;
	struct 	s_arg	*left;
	struct	s_arg	*middle;
	struct  s_arg	*right;
}					t_arg;

int		ft_recognize_builtin_command(char *str);
void	ft_put_command_errors(char *str);
void	ft_print_current_directory(void);
char	**ft_find_prog_path(char *arg);
char	*ft_find_my_prog_path(char *arg);
int		ft_change_dir(char *str);
char	*ft_file_to_string();
void	ft_echo(char **str);
void	ft_put_env();
void	ft_sort_setenv(char **args);
char	**ft_setenv(char **name, int new_environ_size);
t_arg	*ft_store_args(char	*line, t_arg *first);
void	ft_launch_processes(char **arguments);
void	ft_complete_command(int quote_type, char *command_line);
int		ft_check_commas(char *str);
void	ft_recognize_processes(char *str);
char	**ft_split_whitespaces_not_quotes(char *str);
char	*ft_advance_string_for_quote(char *str);
void	ft_unsetenv(char **str);
void	ft_env(char **args);

# include <unistd.h>

#endif 
