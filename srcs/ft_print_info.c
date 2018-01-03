/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 09:21:23 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 13:04:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <term.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

static int g_x = 0;
static int g_y = 0;

int	ft_putchar_terminal(char c)
{
	int	window_col = 0;

	window_col = window_info(1);
	g_x = 0;
	g_y = 0;
	get_cursor_position(&g_x, &g_y);
	if (!(get_terminal_description()))
		return (0);
	if (window_col > g_x)
	{
		ft_putchar(c);
		g_x++;
	}
	else
	{
		g_x = 2;
		g_y++;
		ft_putchar('\n');
		ft_putchar(c);
	}
	return (1);
}

void ft_print_current_directory(void)
{
	char	*path;
	char	*git;

	path = NULL;
	git = NULL;
	ft_get_location_info(&path, &git);
	if (path)
	{
		ft_putstr("\e[0;91m");
		ft_putchar('/');
		ft_putstr(path);
		if (git)
		{
			ft_putstr("\e[0m");
			ft_putstr("\e[0;90m");
			git ? ft_putstr("[git@]") : 0;
			git ? ft_putstr(git) : 0;
		}
	}
	ft_putstr("\\ ");
	ft_putstr("\e[0m");
	if (git)
		ft_memdel((void**)&git);
}

int	erase_input()
{
	g_x = 0;
	g_y = 0;
	get_cursor_position(&g_x, &g_y);
	if (!(get_terminal_description()))
		return (0);
	if (g_x != 2)
	{
		tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		tputs(tgetstr("dc", NULL), 0, &int_ft_putchar);
	}
	else if (g_x == 2)
	{
		tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		tputs(tgetstr("dc", NULL), 0, &int_ft_putchar);
		tputs(tgoto(tgetstr("cm", NULL), window_info(1) - 1, g_y - 2), 0, &int_ft_putchar);
	}
	return (1);
}
static int get_file_descriptor(void)
{

	char		*dev;
	int         fd;

	dev = NULL;
	fd = -1;
	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY)) != -1)
		return (fd);
	else
		return (-1);
}

void	print_handler(int fd, char c, int print)
{
	struct flock	lock;
	int 			forkk;

	forkk = -1;
	fd = get_file_descriptor();
	if (!(forkk = fork()))
	{
		lock.l_type = F_WRLCK | F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		if (fcntl (fd, F_SETLK, &lock) == -1)
		{
			put_fatal_error("couldn't lock the fd to write on it");
			exit (0);
		}
		if (print)
			ft_putchar_terminal(c);
		else
			erase_input();
		fcntl(fd, F_UNLCK, &lock);
		exit (0);
	}
	else
		wait (&forkk);
}
