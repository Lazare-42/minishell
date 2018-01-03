/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bg_y: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 bg_y lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 04:16:12 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <term.h>

static int g_x = 0;
static int g_y = 0;

int	ft_putchar_terminal(char c)
{
	int	window_col = 0;

	window_col = window_info(1);
	g_x = 0;
	g_y = 0;
	if (!(get_cursor_position(&g_x, &g_y)))
		put_fatal_error("\ncould not get localisation info after printing dir");
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
	g_x = 0;
	g_y = 0;
	if (!(get_cursor_position(&g_x, &g_y)))
		put_fatal_error("\ncould not get localisation info after printing dir");
}

int	erase_input(t_arg **new)
{
	g_x = 0;
	g_y = 0;
	if (!(get_cursor_position(&g_x, &g_y)))
		put_fatal_error("\ncould not get localisation info after printing dir");
	(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
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
		if (!(get_cursor_position(&g_x, &g_y)))
			put_fatal_error("\ncould not get localisation info after printing dir");
	}
	return (1);
}
