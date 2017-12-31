#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

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

	if (read(fd, &buffer, 1) == -1)
		return (0);
	return (buffer[0]);
}

void	get_cursor_position(int *x, int *y)
{
	struct termios	saved;
	struct termios	temporary;
	int				result;
	char			*dev;

	result = 0;
	fd = -1;
	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY)) == -1)
	{
			ft_putstr("could not open fd");
			return ;
	}
	ft_putnbr(fd);
	if (tcgetattr(fd, &saved) != 0)
		return ;
	if (tcgetattr(fd, &temporary) != 0)
		return ;
	temporary.c_lflag &= (CREAD);
	temporary.c_lflag &= (IGNBRK);
	temporary.c_lflag &= (ICANON);
	if (tcsetattr(fd, TCSANOW, &temporary) != 0)
		return ;
	if ((write_cursor()))
	{
		if ((result = read_cursor()) != 27)
		{
			ft_putstr("not an escape sequence");
			return ;
		}
		if ((result = read_cursor()) != '[')
		{
			ft_putstr("not a [");
			return ;
		}
		result = read_cursor();
		while (result >= '0' && result <= '9')
			*y = 10 * *y + result - '0';
		if ((result = read_cursor()) != ';')
		{
			ft_putstr("error");
			return ;
		}
		while (result >= '0' && result <= '9')
			*x = 10 * *x + result - '0';
		ft_putnbr(*x);
		ft_putnbr(*y);
		if ((result = read_cursor()) != 'R')
		{
			ft_putstr("not a R");
			return ;
		}
	}
	if (tcsetattr(fd, TCSANOW, &saved) != 0)
	{
		ft_putstr("could not set values");
		return ;
	}
}
