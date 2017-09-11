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

int		ft_recognize_builtin_command(char *str);
void	ft_put_command_errors(char *str);
void	ft_print_current_directory();
char	**ft_find_prog_path(char *arg);
int		ft_change_dir(char *str);
char	*ft_file_to_string();
void	ft_echo(char **str);
void	ft_put_env();
void	ft_sort_setenv(char **args);
void	ft_setenv(char *name, char *value);

# include <unistd.h>

#endif 
