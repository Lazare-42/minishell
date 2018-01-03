/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bg_y: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 bg_y lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 06:54:14 by lazrossi         ###   ########.fr       */
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
	if (!(get_cursor_position(&g_x, &g_y)))
		put_fatal_error("\ncould not get cursor pos before printing a char");
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
	if (!(get_cursor_position(&g_x, &g_y)))
		put_fatal_error("\ncould not get cursor pos to erase");
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

int		print_handler(int fd, char c, int print)
{
	struct flock	lock;
	int 			forkk;

	forkk = -1;
	if (!(forkk = fork()))
	{
		lock.l_type = F_WRLCK;
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
	return (1);
}
