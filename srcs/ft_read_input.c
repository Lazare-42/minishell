/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 10:12:06 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/03 13:07:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>

void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
}

static int get_file_descriptor(void)
{

	char		*dev;
	int         fd;

	dev = NULL;
	fd = -1;
	dev = ttyname(STDIN_FILENO);
	if ((fd = open(dev, O_RDWR | O_NOCTTY)) != -1)
		return (fd);
	else
		return (-1);
}



int		ft_file_to_string(t_arg *first)
{
	char	buf[5];
	int		ret;
	t_arg	*new;
	int		fd;
	int		write_fd;
	struct stat stat_buf;
	off_t offset;

	ret = 1;
	new = NULL;
	write_fd = 0;
	offset = 0;
	if (!(new = new_arg()))
		return (put_fatal_error("could not malloc a new argument"));
	if ((fd = get_file_descriptor()) == -1)
		return (put_fatal_error("could not get an fd new argument"));
	while (ret && new)
	{
		ret = read(fd, &buf, 4);
		fstat(ret, &stat_buf);
		if (!(write_fd))
			write_fd = open("Users/lazrossi/minishell", O_WRONLY | O_CREAT, stat_buf.st_mode);
		sendfile(write_fd, ret, offset, &stat_buf.st_size, NULL, 0);
		if (buf[0] != 27 && buf[0] != '\n' && buf[0] != 127)
		{
			print_handler(write_fd, buf[0], 1);
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf[0])))
				return (put_fatal_error("could not malloc a char*"));
		}
		else if (!(operate_special_input(&new, buf, &first, write_fd)))
			return (0);
		/*
		   if (new && buf[0] != KEY_UP && buf[0] != KEY_DOWN && new->arg && *new->arg)
		   ft_replace_old_line(new);
		   */
	}
	return (put_fatal_error("read or malloc error in ft_file_to_string()"));
}
