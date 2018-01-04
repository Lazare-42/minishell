/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_special_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:04:08 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 14:13:39 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static	t_arg	*g_to_find = NULL;

/*
**		((*new)->old_line) ? ft_memdel((void**)&(*new)->old_line) : NULL;
**		(*new)->arg = ((*new)->line_right) ?
**		ft_strjoinfree(&(*new)->arg, &(*new)->line_right, 'B') : (*new)->arg;
**		*first = (*((*new)->arg)) ? ft_store_args(*first, *new) : *first;
**		(*new) = new_arg();
**		(*(*new)->arg) ? ft_look_inside((*new)->arg, first) : 0;
*/

static void	operate_cr(char *str)
{
	if (str)
	{
		g_to_find = NULL;
		ft_look_inside(str, NULL);
		ft_memdel((void**)&str);
	}
	ft_print_current_directory();
}

/*
**   static void	operate_key_left(t_arg **new)
**   {
**   int len;
**
**   if ((*new) && (*new)->arg)
**   {
**   len = ft_strlen((*new)->arg) - 1;
**   if ((*new)->line_right && (*new)->line_right[0])
**   (*new)->line_right =
**   ft_strjoinfree_char_str((*new)->arg[len], &(*new)->line_right);
**   else
**   (*new)->line_right = ft_strdup(&(*new)->arg[len]);
**   (*new)->arg[len] = '\0';
**   }
**   }
**
**   static void	operate_key_right(t_arg **new)
**   {
**   if (*new && (*new)->line_right && (*new)->line_right[0])
**   {
**   (*new)->arg = ft_strjoinfree_str_char(&(*new)->arg, (*new)->line_right[0]);
**   (*new)->line_right =
**   ft_strdupfrom_free((const char**)&((*new)->line_right), 1);
**   }
**   }
*/

/*
**	else if (buf[0] == 127 && (*new)->arg && *(*new)->arg)
**		erase_input(new);
**	else if (buf[0] == 27 && buf[1] == '[')
**	{
**		if (buf[2] == 'A')
**			debug();
**		if (buf[2] == 'B')
**			ft_putstr("hey down");
**		   ft_advance_lst_to(*first, *new, &g_to_find, 1);
**		   if (buf == KEY_DOWN && *first && g_to_find)
**		   ft_advance_lst_to(*first, *new, &g_to_find, 0);
**		   if (buf == KEY_LEFT && (*new)->arg && *(*new)->arg)
**		   operate_key_left(new);
**		   if (buf == KEY_RIGHT && (*new)->arg && *(*new)->arg)
**		   operate_key_right(new);
**		   }
*/

int			operate_special_input(t_arg **new, char *buf, t_arg **first)
{
	operate_cr(buf);
	first = NULL;
	new = NULL;
	return (1);
}
