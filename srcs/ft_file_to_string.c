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

t_arg *args;
char  *line_found;

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

void ft_replace_content(char *line)
{
	ft_putchar('\r');
	ft_print_current_directory();
	(line) ? ft_putstr(line) : 0;
}

int 	ft_check_input_for_ctrl_keys(char **line, int buf)
{
	line_found = NULL;
	if (buf == KEY_UP)
	{
		line_found = ft_advance_lst_to(args, *line);
		if (line_found)
			*line = line_found;
		return (0);
	}
	if (buf == KEY_DOWN)
	{
		return (0);
	}
	if (buf == KEY_LEFT)
	{
		return (0);
	}
	if (buf == KEY_RIGHT)
	{
		return (0);
	}
	return (1);
}

int ft_check_input_for_special_input(char **line, int buf)
{
	if (line && *line && **line && buf == 127)
	{
		(*line)[ft_strlen(*line) - 1] = ' ';
		ft_putchar('\r');
		ft_print_current_directory();
		ft_putstr(*line);
		(*line)[ft_strlen(*line) - 1] = '\0';
		ft_replace_content(*line);
	}
	if (buf == 127)
		return (0);
	if (*line && buf == '\n')
	{
		line_found = NULL;
		args = ft_store_args(*line, args);
		ft_putchar('\n');
		ft_look_inside(*line);
		*line = ft_strnew(0);
		return (0);
	}
	return (ft_check_input_for_ctrl_keys(line, buf));
}


char	*ft_file_to_string()
{
	long  buf;
	char *line;
	int ret;


	ret = 1;
	line = ft_strnew(0);
	if (!(set_non_canonical_input()))
		return (NULL);
	args = NULL;
	line_found = NULL;
	while (ret)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (ft_check_input_for_special_input(&line, buf)) 
			line = ft_strjoin(line, (char*)&buf);
		ft_replace_content(line);
	}
	return (NULL);
}
