/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/31 02:37:10 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>
#include <stdlib.h>
#include <term.h>
#include <stdio.h>
#include <curses.h>
#include <sys/ioctl.h>

static int	get_cursor_position(void)
{
	struct termios	saved;
	struct termios	temporary;
	int				retval;
	int				result;
	int				rows;
	int				cols;

	if (tcgetattr(0, &saved) != 0)
		return (0);
	if (tcgetattr(0, &temporary) != 0)
		return (0);
	temporary.c_lflag &= (CREAD);
	if (tcsetattr(0, TCSANOW, &temporary) != 0)
		return (0);
	retval = wr(tty, "\033[6n", 4);
	if (tcsetattr(0, TCSANOW, &saved) != 0)
		return (0);
	return (1);
}

int window_info(int info_request)
{
	struct winsize window;

	if (ioctl(1, TIOCGWINSZ, &window) == -1)
		put_error("ioctl error");
	if (info_request == 1)
		return (window.ws_col);
	if (info_request == 2)
		return (window.ws_row);
	return (0);
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

int	erase_input(void)
{
	if (!(get_terminal_description()))
		return (0);
	tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
	tputs(tgetstr("dc", NULL), 0, &int_ft_putchar);
	return (1);
}
