/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:30:36 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/08 15:59:15 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./include/libft.h"
# include "./include/get_next_line.h"
# include <stdlib.h>

char	*ft_str_join_free(char **s1, char **s2)
{
	char *str;

	if (!(str = ft_strjoin(*s1, *s2)))
		return (0);
	ft_memdel((void*)s1);
	return (str);
}

int		ft_fillup(char **line, t_gnl **stock)
{
	if ((*stock)->rest && ft_strchr((*stock)->rest, '\n'))
	{
		if (!(*line = ft_strnew((ft_strchr((*stock)->rest, '\n') - (*stock)->rest))))
			return (-1);
		*line = ft_strncpy(*line, (*stock)->rest, \
				((ft_strchr((*stock)->rest, '\n') - (*stock)->rest)));
		(*stock)->rest = ft_strcpy((*stock)->rest,
				ft_strchr((*stock)->rest, '\n') + 1);
		return (1);
	}
	else if ((*stock)->rest && *(*stock)->rest)
	{
		if (!(*line = ft_strnew(ft_strlen((*stock)->rest))))
			return (-1);
		if (!(*line = ft_strdup((*stock)->rest)))
			return (-1);
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
	if (!(new = malloc(sizeof(t_gnl))) || (!(new->rest = ft_strnew(0))))
		return (0);
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

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!(tmp = manage_stock(&stock, fd)))
		return (-1);
	while ((ft_strchr(buf, '\n') == NULL))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (ret == 0)
			break;
		buf[ret] = '\0';
		if (!(tmp->rest = ft_str_join_free(&tmp->rest, &buf)))
			return (-1);
	}
	ft_strdel(&buf);
	return (ft_fillup(line, &tmp));
}
