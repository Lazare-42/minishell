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
#include "fcntl.h"
#include "unistd.h"


#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_file_to_string()
{
	char *buf;
	char *result;
	int ret;
	struct termios termios_cpy;

	if 	(tcgetattr(0, &termios_cpy) != 0)
		return NULL;
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return NULL;

	ret = 1;
	buf = ft_strnew(1);
	result = ft_strnew(0);
	while (ret == 1)
	{
		ret = read(0, buf, 1);
		buf[1] = '\0';
		if (buf[0] == 127)
		{
			result[ft_strlen(result) - 1] = ' ';
			ft_putchar('\r');
			ft_print_current_directory();
			ft_putstr(result);
			result[ft_strlen(result) - 1] = '\0';
		}
		else
		{
			result = ft_strjoinfree(&result, &buf, 'L');
		}
		ft_putchar('\r');
		ft_print_current_directory();
		ft_putstr(result);
		if (buf[0] == '\n')
		{
			ft_look_inside(result);
			result = ft_strnew(0);
		}
	}
	return (NULL);
}
