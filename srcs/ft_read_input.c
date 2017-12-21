/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/12/21 17:54:09 by lazrossi         ###   ########.fr       */
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


void		ft_file_to_string(void)
{
	long	buf;
	int		ret;
	t_arg	*first;
	t_arg	*new;
	t_arg	*to_find;

	ret = 1;
	first = NULL;
	new = NULL;
	to_find = NULL;
	if (!(set_non_canonical_input()) || (!(first = ft_store_args(first, NULL))))
		return ; 
	if (!(new = new_arg()))
		return ;
	while (ret && new)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (new && ft_check_special_input(&new, buf, &first))
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf)))
				return ;
		ft_replace_content(new);
		if (new && buf != KEY_UP && buf != KEY_DOWN && new->arg)
			new->old_line = ft_strdup(new->arg);
	}
}
