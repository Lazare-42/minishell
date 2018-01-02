/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   ndeated: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/12/31 02:18:12 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
}

int		ft_file_to_string(t_arg *first)
{
	int		buf;
	int		ret;
	t_arg	*new;
	t_arg	*to_find;

	ret = 1;
	new = NULL;
	to_find = NULL;
	if (!(new = new_arg()))
		return (put_fatal_error("could not malloc a new argument"));
	while (ret && new)
	{
		ret = read(0, &buf, 3);
		if (buf != 27 && buf != '\n' && buf != 127)
		{
			if (!(ft_putchar_terminal(buf)))
				return (0);
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf)))
				return (put_fatal_error("could not malloc a char*"));
		}
		if (buf == 27 || buf == '\n' || buf == 127)
			operate_special_input(&new, buf, &first);
		if (new && buf != KEY_UP && buf != KEY_DOWN && new->arg && *new->arg)
			ft_replace_old_line(new);
	}
	return (put_fatal_error("read or malloc error in ft_file_to_string()"));
}
