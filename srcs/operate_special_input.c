/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_input_for_ctrl_keys.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 06:19:14 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 09:09:42 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static	t_arg	*g_to_find = NULL;

static void	operate_cr(t_arg **new, t_arg **first, int fd)
{
	((*new)->line_right) ? ft_putstr_fd((*new)->line_right, fd) : 0;
	ft_putchar('\n');
	if ((*new)->arg)
	{
		g_to_find = NULL;
		((*new)->old_line) ? ft_memdel((void**)&(*new)->old_line) : NULL;
		(*new)->arg = ((*new)->line_right) ? ft_strjoinfree(&(*new)->arg, &(*new)->line_right, 'B') : (*new)->arg;
		*first = (*((*new)->arg)) ? ft_store_args(*first, *new) : *first;
		(*(*new)->arg) ? ft_look_inside((*new)->arg, first) : 0;
		(*new) = new_arg();
	}
	print_handler(0, RESET_HISTORIC, 0);
	ft_print_current_directory();
}

static void	operate_key_left(t_arg **new, int fd)
{
	int len;

	if ((*new) && (*new)->arg)
	{
		len = ft_strlen((*new)->arg) - 1;
		if ((*new)->line_right && (*new)->line_right[0])
			(*new)->line_right = ft_strjoinfree_char_str((*new)->arg[len], &(*new)->line_right);
		else
			(*new)->line_right = ft_strdup(&(*new)->arg[len]);
		(*new)->arg[len] = '\0';
	}
	if ((*new) && (*new)->arg && (*(*new)->arg || *(*new)->line_right))
		print_handler((*new)->arg, KEY_LEFT, fd);
}

static void	operate_key_right(t_arg **new, int fd)
{
	if ((*new)->line_right && *(*new)->line_right)
		print_handler(NULL, KEY_RIGHT, fd);
	if (*new && (*new)->line_right && (*new)->line_right[0])
	{
		(*new)->arg = ft_strjoinfree_str_char(&(*new)->arg, (*new)->line_right[0]);
		(*new)->line_right = ft_strdupfrom_free((const char**)&((*new)->line_right), 1); 
	}
}

static void operate_del(t_arg **new, int fd)
{
		print_handler(&(*new)->arg[ft_strlen((*new)->arg) -1], -1, fd);
		(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
		(*new)->old_line = NULL;
}

int			operate_special_input(t_arg **new, char *buf, t_arg **first, int fd)
{
	if (buf[0] == '\n')
		operate_cr(new, first, fd);
	else if (buf[0] == 127 && (*new)->arg && *(*new)->arg)
		operate_del(new, fd);
	else if ( buf[0] && buf [1] && buf[2] && buf[0] == 27 && buf[1] == '[')
	{
		if (buf[2] == 'A')
			ft_advance_lst_to(*first, *new, &g_to_find, 1);
		else if (buf[2] == 'B')
			ft_advance_lst_to(*first, *new, &g_to_find, 0);
		if (buf[2] == 'A' || buf[2] == 'B')
			print_handler((*new)->arg, HISTORIC, fd);
		if (buf[2] == 'C' && (*new)->arg)
			operate_key_right(new, fd);
		if (buf[2] == 'D' && (*new)->arg && *(*new)->arg)
			operate_key_left(new, fd);
	}
	return (1);
}
