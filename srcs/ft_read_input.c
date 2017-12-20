/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/12/20 10:20:10 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static int	set_non_canonical_input(void)
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

static int	ft_check_special_input(t_arg **new, int buf, t_arg **first_arg)
{
	char *to_erase;

	to_erase = NULL;
	if ((*new)->arg && *(*new)->arg && buf == 127)
	{
		to_erase = ft_strdup((*new)->arg);
		(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
		ft_replace_content(to_erase, (*new)->arg, (*new)->line_right);
	}
	if ((*new)->arg && buf == '\n')
	{
		((*new)->old_line) ? ft_memdel((void**)&(*new)->old_line) : NULL;
		if ((*new)->line_right)
			(*new)->arg = ft_strjoinfree(&(*new)->arg,
					&(*new)->line_right, 'B');
		(*new)->line_right = NULL;
		(*(*new)->arg) ? *first_arg = ft_store_args((*new), *first_arg) : 0;
		(*first_arg) ? ft_clean_lst_for_line_pos(*first_arg) : 0;
		ft_putchar('\n');
		(*(*new)->arg) ? ft_look_inside((*new)->arg) : 0;
		(*new) = new_arg();
	}
	if (buf == 127 || buf == '\n')
		return (0);
	return (ft_check_input_for_ctrl_keys(new, buf, *first_arg));
}

void		ft_file_to_string(void)
{
	long	buf;
	int		ret;
	t_arg	*first;
	t_arg	*new;

	ret = 1;
	first = NULL;
	new = NULL;
	new = NULL;
	if (!(set_non_canonical_input()))
		return ;
	if (!(first = ft_store_args(first, NULL)))
		return ;
	if (!(new = new_arg()))
		return ;
	while (ret)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (ft_check_special_input(&new, buf, &first))
			new->arg = ft_strjoinfree_str_char(&((new)->arg), buf);
		(new->arg) ? ft_replace_content(NULL, new->arg, new->line_right) : 0;
		(buf != KEY_UP && buf != KEY_DOWN && new->arg) ? new->old_line =
			ft_strdup(new->arg) : 0;
	}
}
