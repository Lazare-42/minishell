/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_location_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:22:58 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 21:41:26 by lazrossi         ###   ########.fr       */
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

static int g_print_size;

static	char	*get_last_part(char *tmp)
{
	int		i;

	i = 0;
	if (tmp)
		i = ft_strlen(tmp);
	if (i > 1)
		i--;
	while (i && tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	return (&tmp[i]);
}

char			*ft_sort_git_name(DIR *dir, char *buf)
{
	char			*path;
	struct dirent	*dent;
	int				fd;
	int				ret;

	fd = -1;
	while (dir && (dent = readdir(dir)))
	{
		if (ft_memcmp(dent->d_name, "HEAD", 4) == 0)
		{
			path = ft_strjoin(getcwd(dent->d_name, 1024), "/.git/HEAD");
			fd = open(path, O_RDONLY);
			ret = read(fd, buf, 1024);
			(ret != -1) ? buf[ft_strlen(buf) - 1] = '\0' : 0;
			buf = get_last_part(buf);
			(path) ? ft_strdel(&path) : 0;
			close(fd);
		}
	}
	return (buf);
}

static char		*ft_get_git(void)
{
	DIR				*dir;
	char			*buf;
	char			*path;

	path = NULL;
	buf = NULL;
	if ((dir = opendir(".git")))
	{
		if (!(buf = ft_strnew(1025)))
			return (NULL);
		buf = ft_sort_git_name(dir, buf);
		closedir(dir);
	}
	return (buf);
}

void			ft_get_location_info(char **path, char **git)
{
	int		i;

	i = 0;
	g_print_size = 0;
	if (!(*path = ft_strnew(1024)))
		return ;
	*path = getcwd(*path, 1024);
	if (*path)
		*path = get_last_part(*path);
	else
		ft_putstr_fd("! getcwd() failed, unknown shell location !", 2);
	*git = ft_get_git();
}
