/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_location_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:22:58 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 11:48:56 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
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
			(ret != -1) ? buf[ret - 1] = '\0' : 0;
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
	char			*tmp;

	tmp = NULL;
	buf = NULL;
	if ((dir = opendir(".git")))
	{
		if (!(buf = ft_strnew(1025)))
			return (NULL);
		tmp = buf;
		buf = ft_sort_git_name(dir, buf);
		buf = ft_strdup(buf);
		ft_memdel((void**)&tmp);
		closedir(dir);
	}
	return (buf);
}

static int		set_pwd_var(void)
{
	extern char **environ;
	char		*path;

	if (!(path = ft_strnew(1024)))
		return (0);
	if (!(path = getcwd(path, 1025)))
	{
		ft_memdel((void**)&path);
		path = ft_strdup("! getcwd() failed, unknown shell location !\n");
	}
	if (!(path = ft_strjoinfree_one(&path, "PWD=", 'B')))
		return (0);
	if (!(environ = ft_tabdup_add_free(&environ, &path, 'B')))
	{
		ft_memdel((void**)&path);
		return (0);
	}
	ft_memdel((void**)&path);
	return (1);
}

void			ft_get_location_info(char **path, char **git)
{
	int				i;
	extern	char	**environ;

	i = 0;
	g_print_size = 0;
	while (environ && environ[i] && ft_memcmp(environ[i], "PWD", 3))
		i++;
	if (environ && environ[i])
		*path = &environ[i][4];
	else
	{
		if ((set_pwd_var()))
			ft_get_location_info(path, git);
		else
			return ;
	}
	*path = get_last_part(*path);
	*git = ft_get_git();
}
