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
#include "../libft/includes/libft.h"
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

void ft_putstr_terminal(char *str, int fd)
{
	int new_cursor_pos;

	new_cursor_pos = 0;
	g_x = 0;
	g_y = 0;
	get_cursor_position(&g_x, &g_y, fd);
	new_cursor_pos = g_x + (int)ft_strlen(str) - 1;
	if (g_y == window_info(2))
	{
		while (new_cursor_pos > window_info(1)) 
		{
			new_cursor_pos -= window_info(1);
			g_y--;
		}
	}
	if (((g_x + (int)ft_strlen(str)) / window_info(1)) > (window_info(2) - g_y))
		g_y--;
	ft_putstr_fd(str, fd);
	tputs(tgoto(tgetstr("cm", NULL), g_x - 1, g_y - 1), 0, &int_ft_putchar);
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
	int		move_y;

	move_y = 0;
	strlen = ft_strlen(str);
	tputs(tgoto(tgetstr("cm", NULL), 0, g_y - 1), 0, &int_ft_putchar);
	tputs(tgetstr("cd", NULL), 0, &int_ft_putchar);
	ft_print_current_directory();
	ft_putstr_fd(str, fd);
	move_y = (strlen + g_x) / window_info(1) - (window_info(2) - g_y);
	if (move_y > 0)
	{
		g_y -=  move_y;
		if (g_y < 0)
			g_y = 0;
	}
}

void	print_handler(char *c, int print, int fd)
{
	static int first_historic = 0;

	if (print == 1)
		ft_putchar_terminal(*c, fd);
	else if (print == 2)
		ft_putstr_terminal(c, fd);
	else if (print == -1)
		erase_input(fd);
	else if (print == KEY_LEFT)
	{
		g_x = 0;
		g_y = 0;
		get_cursor_position(&g_x, &g_y, fd);
		if (g_x == 1)
		{
			tputs(tgoto(tgetstr("cm", NULL), window_info(1) - 1, g_y - 2), 0, &int_ft_putchar);
			tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		}
		else 
			tputs(tgetstr("le", NULL), 0, &int_ft_putchar);
		g_x = 0;
		g_y = 0;
		get_cursor_position(&g_x, &g_y, fd);
	}
	else if (print == KEY_RIGHT)
	{
		g_x = 0;
		g_y = 0;
		get_cursor_position(&g_x, &g_y, fd);
		if (g_x == window_info(1))
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, g_y), 0, &int_ft_putchar);
			get_cursor_position(&g_x, &g_y, fd);
		}
		else 
			tputs(tgetstr("nd", NULL), 0, &int_ft_putchar);
		g_x = 0;
		g_y = 0;
		get_cursor_position(&g_x, &g_y, fd);
	}
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
