/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:14 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 11:37:54 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <term.h>

int		main(void)
{
	extern char **environ;
	t_arg		*first;

	first = NULL;
	first = ft_store_args(first, NULL);
	if (!(environ = ft_tabdup(environ, ft_tabsize(environ))))
		return (put_fatal_error("malloc error while copying tab"));
	ft_print_current_directory();
	return (ft_file_to_string(first));
}
