/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:01:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/22 14:44:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# define BUFF_SIZE 2056

# include <unistd.h>

int					get_next_line(const int fd, char **line, char to_find);
typedef	struct		s_gnl
{
	char			*rest;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;
#endif
