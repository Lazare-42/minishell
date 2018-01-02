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
#include <fcntl.h>

void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
}

static int get_file_descriptor(void)
{

	char *dev;
	int         fd;

	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY)) != -1)
		return (fd);
	else
		return (-1);
}



int		ft_file_to_string(t_arg *first)
{
	char	buf[5];
	int		ret;
	t_arg	*new;
	t_arg	*to_find;
	int		fd;

	ret = 1;
	new = NULL;
	to_find = NULL;
	if (!(new = new_arg()))
		return (put_fatal_error("could not malloc a new argument"));
	if ((fd = get_file_descriptor()) == -1)
		return (put_fatal_error("could not get an fd new argument"));
	while (ret && new)
	{
		ret = read(fd, &buf, 4);
		if (buf[0] != 27 && buf[0] != '\n' && buf[0] != 127)
		{
			if (!(ft_putchar_terminal(buf[0])))
				return (0);
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf[0])))
				return (put_fatal_error("could not malloc a char*"));
		}
		else if (!(operate_special_input(&new, buf, &first)))
			return (0);
		/*
		if (new && buf[0] != KEY_UP && buf[0] != KEY_DOWN && new->arg && *new->arg)
			ft_replace_old_line(new);
			*/
	}
	return (put_fatal_error("read or malloc error in ft_file_to_string()"));
}
