/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/09/07 17:13:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

char  *old_line;
t_arg *to_find;
t_arg *first_arg;

int	set_non_canonical_input()
{
	struct termios termios_cpy;

	if 	(tcgetattr(0, &termios_cpy) != 0)
		return (0);
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return (0);
	return (1);
}

void ft_replace_content(char *old_content, char *new_content, int erase)
{
	ft_print_current_directory();
	if (erase)
	{
		ft_putwhites(ft_strlen(old_content));
		ft_print_current_directory();
	}
	ft_putstr(new_content);
}

int 	ft_check_input_for_ctrl_keys(char **line, int buf, t_arg *first_arg)
{
	t_arg *tmp;

	tmp = NULL;
	if (buf == KEY_UP)
	{
		if (first_arg && old_line)
		{
			ft_advance_lst_to(first_arg, &to_find, old_line); 
			ft_replace_content(*line, to_find->arg, 1);
			*line = ft_strdup(to_find->arg);
		}
		return (0);
	}
	if (buf == KEY_DOWN)
	{
		if (first_arg && to_find)
		{
			ft_retreat_lst_to(&to_find); 
			(to_find) ? ft_replace_content(*line, to_find->arg, 1) : ft_replace_content(*line, old_line, 1);
			*line = (to_find) ?  ft_strdup(to_find->arg) : ft_strdup(old_line);
		}
		return (0);
	}
	if (buf == KEY_LEFT)
	{
		return (1);
	}
	if (buf == KEY_RIGHT)
	{
		return (1);
	}
	return (1);
}

static int ft_check_input_for_special_input(char **line, int buf, t_arg *first_arg)
{
	char *to_erase;

	to_erase = NULL;
	if (line && *line && **line && buf == 127)
	{
		to_erase = ft_strdup(*line);
		(*line)[ft_strlen(*line) - 1] = '\0';
		ft_replace_content(to_erase, *line, 1);
	}
	if (buf == 127)
		return (0);
	if (*line && buf == '\n')
	{
		to_find = NULL;
		old_line = NULL;
		(old_line) ? ft_strdel(&old_line) : NULL;
		(**line) ? first_arg = ft_store_args(*line, first_arg) : 0;
		(first_arg) ? ft_clean_lst_for_line_pos(first_arg) : 0;
		ft_putchar('\n');
		(**line) ? ft_look_inside(*line) : 0;
		*line = ft_strnew(0);
		return (0);
	}
	return (ft_check_input_for_ctrl_keys(line, buf, first_arg));
}


char	*ft_file_to_string()
{
	long  buf;
	char  *line;
	int ret;


	ret = 1;
	old_line = NULL;
	to_find = NULL;
	first_arg = NULL;
	if (!(line = ft_strnew(0)))
		return (NULL);
	if (!(set_non_canonical_input()))
		return (NULL);
	first_arg = ft_store_args(line, first_arg);
	while (ret)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (ft_check_input_for_special_input(&line, buf, first_arg)) 
			line = ft_strjoin(line, (char*)&buf);
		(line) ? ft_replace_content(NULL, line, 0) : 0;
		(buf != KEY_UP && buf != KEY_DOWN && line) ? old_line = ft_strdup(line) : 0;
	}
	return (NULL);
}
