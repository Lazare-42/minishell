#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

int				fd;

static int		write_cursor(void)
{
	if (write(fd, "\033[6n", 4) == -1)
		return (0);
	return (1);
}

static int 		read_cursor(void)
{
	char buffer[4];
	int n;

	n = 0;
	while (1)
	{
		n = read(fd, &buffer, 1);
		if (n > 0)
			return (buffer[0]);
		else 
			return(0);
	}
}

static	int set_terminal(struct termios *saved)
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

static int reset_terminal(struct termios *saved, char *error_message)
{
	if (error_message)
	{
		ft_putstr("\nError while getting cursor position : ");
		ft_putstr(error_message);
		ft_putchar('\n');
	}
	if (tcsetattr(fd, TCSANOW, saved) != 0)
	{
		ft_putstr(" Could also not reset terminal to functionnal values");
		ft_putstr(" Exiting...\n");
		return (0);
	}
	return (1);
}

int		get_cursor_position(int *x, int *y)
{
	struct termios	saved;
	int				result;
	char			*dev;

	result = 0;
	fd = -1;
	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY) == -1) || !(set_terminal(&saved)))
		return (put_fatal_error("termios or fd error in get_cursor_position"));
	if ((write_cursor()))
	{
		if ((result = read_cursor()) != 27)
			return (reset_terminal(&saved, "not an escape sequence"));
		if ((result = read_cursor()) != '[')
			return (reset_terminal(&saved, "not a ["));
		result = read_cursor();
		while (result >= '0' && result <= '9')
		{
			*y = 10 * *y + result - '0';
			result = read_cursor();
		}
		if ((result = read_cursor()) != ';')
			return (reset_terminal(&saved, "not a ;"));
		while (result >= '0' && result <= '9')
		{
			*x = 10 * *x + result - '0';
			result = read_cursor();
		}
		if ((result = read_cursor()) != 'R')
			return (reset_terminal(&saved, "not a R"));
	}
	return (reset_terminal(&saved, NULL));
}
