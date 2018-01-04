/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:27:02 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 11:29:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <fcntl.h>

static int	get_file_descriptor(void)
{
	char	*dev;
	int		fd;

	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY)) != -1)
		return (fd);
	else
		return (-1);
}

int			ft_file_to_string(t_arg *first)
{
	char	*buf;
	int		fd;

	buf = NULL;
	first = NULL;
	if ((fd = get_file_descriptor()) == -1)
		return (put_fatal_error("could not get an fd new argument"));
	while (42)
	{
		if (get_next_line(fd, &buf, '\n'))
			operate_special_input(NULL, buf, NULL);
	}
	return (put_fatal_error("read or malloc error in ft_file_to_string()"));
}
