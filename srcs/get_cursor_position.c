/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 04:15:03 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 12:06:16 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

static int	read_cursor(int fd)
{
	char	buffer[4];
	int		n;

	n = 0;
	while (1)
	{
		n = read(fd, &buffer, 1);
		if (n > 0)
			return (buffer[0]);
		else
			return (0);
	}
}

static	int	set_terminal(struct termios *saved, int fd)
{
	struct termios	temporary;

	if (tcgetattr(fd, &temporary) != 0)
	{
		ft_putstr("\nUnable to tcgetattr to temporary termios");
		return (0);
	}
	if (tcgetattr(fd, saved) != 0)
	{
		ft_putstr("\nUnable to tcgetattr to reset termios");
		return (0);
	}
	temporary.c_lflag &= (CREAD);
	temporary.c_lflag &= (IGNBRK);
	temporary.c_lflag &= (ICANON);
	if (tcsetattr(fd, TCSANOW, &temporary) != 0)
	{
		ft_putstr("\nUnable to tcsetattr to temporary termios");
		return (0);
	}
	return (1);
}

static int	reset_terminal(struct termios *saved, char *error_message, int fd)
{
	if (error_message)
	{
		ft_putstr("\nError while getting cursor position : ");
		ft_putstr(error_message);
		ft_putchar('\n');
	}
	if (tcsetattr(fd, TCSANOW, saved) != 0)
	{
		if (close(fd))
			ft_putstr("\nCould'nt close fd associated with terminal cursor");
		ft_putstr(" Could also not reset terminal to functionnal values");
		ft_putstr(" Exiting...\n");
		return (0);
	}
	if (error_message)
		return (0);
	return (1);
}

static int	fillup_cursor_position(int *x, int *y, struct termios saved, int fd)
{
	int				result;

	result = 0;
	if ((result = read_cursor(fd)) != 27)
		return (0);
	if ((result = read_cursor(fd)) != '[')
		return (reset_terminal(&saved, NULL, fd));
	result = read_cursor(fd);
	while (result >= '0' && result <= '9')
	{
		*y = 10 * *y + result - '0';
		result = read_cursor(fd);
	}
	if (result != ';')
		return (reset_terminal(&saved, NULL, fd));
	result = read_cursor(fd);
	while (result >= '0' && result <= '9')
	{
		*x = 10 * *x + result - '0';
		result = read_cursor(fd);
	}
	if (result != 'R')
		return (reset_terminal(&saved, NULL, fd));
	return (1);
}

int			get_cursor_position(int *x, int *y)
{
	struct termios	saved;
	int				fd;

	fd = 0;
	if (!(set_terminal(&saved, fd)))
		return (put_fatal_error("could'nt set termios in get cursor position"));
	if (write(fd, "\033[6n", 4) != -1)
	{
		if (!(fillup_cursor_position(x, y, saved, fd)))
			return (0);
	}
	else
		return (reset_terminal(&saved, NULL, fd));
	return (reset_terminal(&saved, NULL, fd));
}
