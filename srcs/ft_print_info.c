/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:37:30 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 13:20:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <sys/xattr.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static char *get_last_part(char *tmp)
{
	int i;
	int	k;

	i = 0;
	k = 0;
	if (tmp)
		i = ft_strlen(tmp);
	k = i;
	if (i > 1)
		i--;
	while (tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	return (&tmp[i]);
}

static void ft_putstr_noret(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void ft_print_git()
{
	DIR				*dir;
	struct dirent	*dent;
	char			*buf;
	char			*path;
	int				fd;
	int				ret;

	path = NULL;
	buf = ft_strnew(1025);
	if ((dir = opendir(".git")))
	{
		while (dir && (dent = readdir(dir)))
		{
			if (ft_memcmp(dent->d_name, "HEAD", 4) == 0)
			{
				path = ft_strjoin(getcwd(dent->d_name, 1024), "/.git/HEAD");
				fd = open(path, O_RDONLY);
				ret = read(fd, buf, 1024);
				(ret != -1 ) ? buf[ft_strlen(buf) - 1] = '\0' : 0;
				ft_putstr("[git@]");
				ft_putstr_noret(get_last_part(buf));
				(path) ? ft_strdel(&path) : 0;
			}
		}
		closedir(dir);
	}
	(buf) ? ft_strdel(&buf) : 0;
}

void		ft_print_current_directory()
{
	char	path[1025];
	char 	*tmp;
	int		i;

	i = 0;
	tmp = getcwd(path, 1024);
	ft_putstr("\e[0;91m");
	if (tmp)
		ft_putstr(get_last_part(tmp));
	else
		ft_putstr_fd("! getcwd() failed, unknown shell location !", 2);
	ft_putstr("\e[0m");
	ft_putstr("\e[0;90m");
	ft_print_git();
	ft_putchar(' ');
	ft_putstr("\e[0m");
}
