/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input_for_ctrl_keys.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 06:19:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/19 11:07:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static t_arg	*g_to_find;

static void	ft_check_key_up(t_arg *first, t_arg **new)
{
	if (first && (*new)->old_line)
	{
		ft_advance_lst_to(first, &g_to_find, (*new)->old_line);
		(g_to_find && (*new)->line_right) ? ft_memdel((void**)&(*new)->line_right) : 0;
		(g_to_find) ? ft_replace_content((*new)->arg, g_to_find->arg, (*new)->line_right)
			: 0;
		(g_to_find) ? (*new)->arg = ft_strdup(g_to_find->arg) : 0;
	}
}

static void	ft_check_key_down(t_arg *first, t_arg **new)
{
	if (first && g_to_find)
	{
		ft_retreat_lst_to(&g_to_find);
		(g_to_find) ? ft_replace_content((*new)->arg, g_to_find->arg, (*new)->line_right) :
			ft_replace_content((*new)->arg, (*new)->old_line, (*new)->line_right);
		(*new)->arg = (g_to_find) ? ft_strdup(g_to_find->arg) : ft_strdup((*new)->old_line);
	}
}

static void	ft_check_key_left(t_arg **new)
{
	char	*to_cpy;
	int		len;

	to_cpy = (*new)->arg;
	len = 0;
	len = ft_strlen(to_cpy);
	to_cpy = ft_strdup(&((*new)->arg)[len - 1]);
	(*new)->line_right = ((*new)->line_right) ?
		ft_strjoinfree(&to_cpy, &(*new)->line_right, 'B') : ft_strnew(1);
	((*new)->line_right) ? (*new)->line_right[0] = (*new)->arg[len - 1] : 0;
	(*new)->arg[len - 1] = '\0';
	ft_replace_content(NULL, (*new)->arg, (*new)->line_right);
}

static void	ft_check_key_right(t_arg **new)
{
	char *c;

	c = NULL;
	if ((*new)->arg && (*new)->line_right)
	{
		if (!(c = ft_strnew(1)))
			return ;
		c[0] = (*new)->line_right[0];
		(*new)->arg = ft_strjoinfree(&(*new)->arg, &c, 'B');
		if ((*new)->line_right[1])
			(*new)->line_right = ft_strdup(&(*new)->line_right[1]);
		else
			ft_strdel(&(*new)->line_right);
	}
}

int			ft_check_input_for_ctrl_keys(t_arg **new, int buf, t_arg *first)
{
	t_arg	*tmp;

	tmp = NULL;
	if (buf == KEY_UP)
		ft_check_key_up(first, new);
	if (buf == KEY_DOWN)
		ft_check_key_down(first, new);
	if (buf == KEY_LEFT  && *(*new)->arg)
		ft_check_key_left(new);
	if (buf == KEY_RIGHT)
		ft_check_key_right(new);
	if (buf == KEY_UP || buf == KEY_DOWN || buf == KEY_LEFT || buf == KEY_RIGHT)
		return (0);
	return (1);
}
