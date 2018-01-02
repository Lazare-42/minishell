/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/31 03:42:49 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>
#include <term.h>


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

int	ft_putchar_terminal(char c)
{
	int	window_col = 0;
	int x = 0;
	int y = 0;

	window_col = window_info(1);
	if (!(get_terminal_description()) || (!(get_cursor_position(&x, &y))))
			return (0);
	if (window_col > x)
		ft_putchar(c);
	else
	{
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

int	erase_input(t_arg **new)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!(get_cursor_position(&x, &y)))
		return (0);
	get_terminal_description();
	(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
	if (x != 2)
	{
		tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		tputs(tgetstr("dc", NULL), 0, &int_ft_putchar);
	}
	else if (x == 2)
	{
		tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		tputs(tgetstr("dc", NULL), 0, &int_ft_putchar);
		tputs(tgoto(tgetstr("cm", NULL), window_info(1) - 1, y - 2), 0, &int_ft_putchar);
	}
	return (1);
}
