/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:13:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 17:13:50 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE 2056

# include "../libft/include/libft.h"

int		ft_recognize_builtin_command(char *str);
void	ft_put_command_errors(char *str);
void	ft_print_current_directory();
char	**ft_find_prog_path();

# include <unistd.h>

#endif 
