/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/12/30 01:56:43 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

static int	get_terminal_description(void)
{
	int		success;
	char	*term_type;
	char	*buffer;

	success = 0;
	term_type = NULL;
	buffer = malloc(sizeof(char) * 2028);
	if (!(term_type = getenv("TERM")))
	{
		ft_putstr("Impossible to locate terminal\n");
		return (0);
	}
	//getting terminal type into buffer passed to tegent
	if ((success = tgetent((char*)&buffer, term_type)) != 1)
		return (0);
	char *cl;

	cl = tgetstr("cl", NULL);
		return (0);
	tputs(cl, 1, ft_putchar);

	return (1);
}

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

void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
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
		if (!(get_terminal_description()))
			return ;
		ret = read(0, &buf, sizeof(long));
		/*
		if (new && ft_check_special_input(&new, buf, &first))
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf)))
				return ;
		ft_replace_content(new, 1);
		if (new && buf != KEY_UP && buf != KEY_DOWN && new->arg)
			ft_replace_old_line(new);
	*/
	}
}
