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
	char *result = "";
	int ret;
	struct termios termios_cpy;

	if 	(tcgetattr(0, &termios_cpy) != 0)
		return NULL;
	cfmakeraw(&termios_cpy);
	termios_cpy.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return NULL;

	ret = 1;
	buf = ft_strnew(0);
	while (ret == 1)
	{
		ret = read(0, buf, 1);
		result = ft_strjoin(result, buf);
		if (buf[0] == '\r')
			ft_look_inside(result);
		else
			ft_putstr(buf);
		ft_bzero(buf, 1);
	}
	return (NULL);
}
