/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input_for_ctrl_keys.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 06:19:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 15:40:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static	t_arg	*g_to_find = NULL;

static void	ft_check_key_up(t_arg *first, t_arg *new)
{
	if (first)
	{
		(g_to_find) ? ft_replace_content(new, 0) : 0;
		ft_advance_lst_to(first, new, &g_to_find, 1);
		(g_to_find) ? ft_replace_content(g_to_find, 1) : 0;
	}
}

static void	ft_check_key_down(t_arg *first, t_arg *new)
{
	if (first && g_to_find)
	{
		(g_to_find) ? ft_replace_content(new, 0) : 0;
		ft_advance_lst_to(first, new, &g_to_find, 0);
		(g_to_find) ? ft_replace_content(g_to_find, 1) : 0;
	}
}

int	ft_check_special_input(t_arg **new, int buf, t_arg **first_arg)
{
	if ((*new)->arg && *(*new)->arg && buf == 127)
	{
		ft_replace_content(*new, 0);
		(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
		ft_replace_content(*new, 1);
	}
	if ((*new)->arg && buf == '\n')
	{
		g_to_find = NULL;
		((*new)->old_line) ? ft_memdel((void**)&(*new)->old_line) : NULL;
		(*new)->arg = ((*new)->line_right) ? ft_strjoinfree(&(*new)->arg, &(*new)->line_right, 'B') : (*new)->arg;
		(*((*new)->arg)) ? *first_arg = ft_store_args(*first_arg, *new) : 0;
		ft_putchar('\n');
		(*(*new)->arg) ? ft_look_inside((*new)->arg, first_arg) : 0;
		ft_replace_content(NULL, 0);
		(*new) = new_arg();
	}
	if (buf == 127 || buf == '\n')
		return (0);
	return (ft_check_input_for_ctrl_keys(new, buf, *first_arg));
}

static void	ft_check_key_left(t_arg **new)
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
}

static void	ft_check_key_right(t_arg **new)
{
	if (*new && (*new)->line_right && (*new)->line_right[0])
	{
		(*new)->arg = ft_strjoinfree_str_char(&(*new)->arg, (*new)->line_right[0]);
		(*new)->line_right = ft_strdupfrom_free((const char**)&((*new)->line_right), 1); 
	}
}

int			ft_check_input_for_ctrl_keys(t_arg **new, int buf, t_arg *first)
{
	t_arg	*tmp;

	tmp = NULL;
	if (buf == KEY_UP)
		ft_check_key_up(first, *new);
	if (buf == KEY_DOWN)
		ft_check_key_down(first, *new);
	if (buf == KEY_LEFT && *(*new)->arg)
		ft_check_key_left(new);
	if (buf == KEY_RIGHT)
		ft_check_key_right(new);
	if (buf == KEY_UP || buf == KEY_DOWN || buf == KEY_LEFT || buf == KEY_RIGHT)
		return (0);
	return (1);
}
