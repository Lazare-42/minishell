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

char	*ft_file_to_string()
{
	char	*buf;
	int		ret;
	int		fd;
	static	char *line = NULL;

	fd = 0;
	ret = 1;
	if (!(line))
	{
		if (!(line = ft_strnew(0)))
			return (NULL);
	}
	if (!(buf = ft_strnew(4096)))
		return (NULL);
	if ((ret = read(fd, buf, 4096)))
	{
		return (buf);
	}
	return (line);
}
