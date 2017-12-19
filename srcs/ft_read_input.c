/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/12/19 11:45:27 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static t_arg	*to_find;

int			set_non_canonical_input(void)
{
	struct termios termios_cpy;

	if (tcgetattr(0, &termios_cpy) != 0)
		return (0);
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return (0);
	return (1);
}

static int	ft_check_special_input(t_arg **new, int buf, t_arg **first)
{
	char *to_erase;

	to_erase = NULL;
	if ((*new)->arg && (*new)->arg[0] && buf == 127)
	{
		if (!(to_erase = ft_strdup((*new)->arg)))
			return (1);
		((*new)->arg)[ft_strlen((*new)->arg) - 1] = '\0';
		ft_replace_content(to_erase, (*new)->arg, (*new)->line_right);
	}
	if ((*new)->arg && buf == '\n')
	{
		to_find = NULL;
//		((*new)->old_line) ? ft_memdel((void**)(*new)->old_line) : NULL;
		(*new)->arg = ((*new)->line_right) ? ft_strjoinfree(&(*new)->arg, 
				&(*new)->line_right, 'B') : (*new)->arg;
		(*(*new)->arg) ? *first = ft_store_args(*first, *new) : 0;
		(*first) ? ft_clean_lst_for_line_pos(*first) : 0;
		ft_putchar('\n');
		(*(*new)->arg) ? ft_look_inside((*new)->arg) : 0;
		(*new)->arg = ft_strnew(0);
	}
	if (buf == 127 || (buf == '\n' && (*new)->arg))
		return (0);
	return (ft_check_input_for_ctrl_keys(new, buf, *first));
}

char		*ft_file_to_string(void)
{
	long	buf;
	int		ret;
	t_arg	*first;
	t_arg	*new;

	ret = 1;
	to_find = NULL;
	first = NULL;
	if (!(set_non_canonical_input()))
		return (NULL);
	first = ft_store_args(first, NULL);
	ft_replace_content(NULL, NULL, NULL);
	if (!(new = new_arg()))
		return (NULL);
	while (ret)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (ft_check_special_input(&new, buf, &first))
			new->arg = ft_strjoinfree_str_char(&(new->arg), (char)buf);
		(new->arg) ? ft_replace_content(NULL, new->arg, new->line_right) : 0;
		(buf != KEY_UP && buf != KEY_DOWN && new->arg) ? new->old_line = ft_strdup(new->arg) : 0;
	}
	return (NULL);
}
