/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 09:21:23 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 14:14:43 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <term.h>

static int g_x = 0;
static int g_y = 0;

int	ft_putchar_terminal(char c, int fd)
{
	int	window_col = 0;

	window_col = window_info(1);
	g_x = 0;
	g_y = 0;
	get_cursor_position(&g_x, &g_y, fd);
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

int		erase_input(int fd)
{
	g_x = 0;
	g_y = 0;
	get_cursor_position(&g_x, &g_y, fd);
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

void	putstr_historic(char *str, int fd)
{
	int		strlen;

	strlen = ft_strlen(str);
	if (strlen > window_info(1) &&
	tputs(tgoto(tgetstr("cm", NULL), 0, g_y - 1), 0, &int_ft_putchar);
	tputs(tgetstr("cd", NULL), 0, &int_ft_putchar);
	ft_print_current_directory();
	ft_putstr_fd(str, fd);
}

void	print_handler(char *c, int print, int fd)
{
	static int first_historic = 0;

	if (print == 1)
		ft_putchar_terminal(*c, fd);
	else if (print == -1)
		erase_input(fd);
	else if (print == HISTORIC)
	{
		if (!first_historic)
		{
			g_x = 0;
			g_y = 0;
			get_cursor_position(&g_x, &g_y, fd);
			first_historic = 1;
		}
		putstr_historic(c, fd);
	}
	if (print == 1 || print == -1 || print == RESET_HISTORIC)
		first_historic = 0;
}
