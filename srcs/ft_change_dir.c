/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:20:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 19:21:09 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>

void	ft_call_to_chdir(char *str, char *arg)
{
	char			path[1025];
	char			*tmp;
	char			*path_var;
	char			*setenv_path[2];
	extern	char	**environ;

	tmp = NULL;
	if (!(path_var = ft_strdup("PWD=")))
		return ;
	if (chdir(str))
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		tmp = getcwd(path, 1024);
		path_var = ft_strjoin(path_var, tmp);
		setenv_path[0] = path_var;
		setenv_path[1] = NULL;
		environ = ft_setenv(setenv_path, ft_tabsize(environ), environ);
		ft_strdel(&path_var);
	}
}

int		ft_change_dir(char *str)
{
	extern char	**environ;
	char		tmp[1025];
	int			i;

	i = 0;
	if (!str)
	{
		while (environ[i] && ft_memcmp(environ[i], "HOME=", 5))
			i++;
		ft_call_to_chdir(&environ[i][5], str);
		return (0);
	}
	if (str && str[0] != '/')
	{
		getcwd(tmp, 1024);
		ft_strcat(tmp, "/");
		ft_strcat(tmp, str);
		ft_call_to_chdir(tmp, str);
		return (0);
	}
	if (!str[1])
		chdir("/");
	ft_call_to_chdir(str, str);
	return (0);
}
