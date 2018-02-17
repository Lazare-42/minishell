/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 04:15:03 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 14:14:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

static char		read_cursor(void)
{
	char buffer;
	int n;

	n = 0;
	while (1)
	{
		n = read(0, &buffer, 1);
		if (n > 0)
			return (buffer);
		else 
			return(0);
	}
}

static void		fillup_cursor_position(int *x, int *y)
{
	int				result;

	result = 0;
	while (result != 27)
		result = read_cursor();
	result = read_cursor();
	while (result != '[')
		result = read_cursor();
	result = read_cursor();
	while (result >= '0' && result <= '9')
	{
		*y = 10 * *y + result - '0';
		result = read_cursor();
	}
	while (result != ';')
		result = read_cursor();
	result = read_cursor();
	while (result >= '0' && result <= '9')
	{
		*x = 10 * *x + result - '0';
		result = read_cursor();
	}
	while (result != 'R')
		result = read_cursor();
	return ;
}

void			get_cursor_position(int *x, int *y, int fd)
{
	if (write(fd, "\033[6n", 4))
		fillup_cursor_position(x, y);
	return ;
}
