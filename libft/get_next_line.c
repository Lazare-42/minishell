/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:30:36 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 18:03:52 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_join_free(char **s1, char **s2)
{
	char *str;

	str = ft_strjoin(*s1, *s2);
	ft_memdel((void*)s1);
	return (str);
}

int		ft_fillup(char **line, t_gnl **stock)
{
	if ((*stock)->rest && ft_strchr((*stock)->rest, '\n'))
	{
		*line = ft_strnew((ft_strchr((*stock)->rest, '\n') - (*stock)->rest));
		*line = ft_strncpy(*line, (*stock)->rest, \
				((ft_strchr((*stock)->rest, '\n') - (*stock)->rest)));
		(*stock)->rest = ft_strcpy((*stock)->rest,
				ft_strchr((*stock)->rest, '\n') + 1);
		return (1);
	}
	else if ((*stock)->rest && *(*stock)->rest)
	{
		*line = ft_strnew(ft_strlen((*stock)->rest));
		*line = ft_strdup((*stock)->rest);
		(*stock)->rest = NULL;
		return (1);
	}
	return (0);
}

t_gnl	*manage_stock(t_gnl **stock, int fd)
{
	t_gnl *tmp;
	t_gnl *new;

	if (*stock)
	{
		tmp = *stock;
		while (tmp->next && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd == fd)
			return (tmp);
	}
	if (!(new = malloc(sizeof(t_gnl))))
		return (NULL);
	new->rest = ft_strnew(0);
	new->fd = fd;
	if (*stock)
	{
		new->next = *stock;
		*stock = new;
		return (new);
	}
	new->next = NULL;
	*stock = new;
	return (*stock);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*stock = NULL;
	t_gnl			*tmp;
	char			*buf;
	int				ret;

	buf = ft_strnew(BUFF_SIZE);
	if (!(tmp = manage_stock(&stock, fd)))
		return (-1);
	ret = 1;
	while ((ft_strchr(buf, '\n') == NULL))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (ret == 0)
		{
			free(buf);
			return (ft_fillup(line, &tmp));
		}
		buf[ret] = '\0';
		tmp->rest = ft_str_join_free(&tmp->rest, &buf);
	}
	free(buf);
	return (ft_fillup(line, &tmp));
}
