/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:20:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 14:55:13 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>

void	ft_call_to_chdir(char *str)
{
	char			path[1025];
	char			*tmp;
	extern	char	**environ;

	tmp = NULL;
	if (!(getcwd(path, 1025)) || (!(tmp = ft_strjoin("OLDPWD=", path))))
		return ;
	if (chdir(str))
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_memdel((void**)&tmp);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		if (!(environ = ft_tab_replacestr(&environ, &tmp, "OLDPWD=\0")))
			return ;
		if (!(getcwd(path, 1025)) || (!(tmp = ft_strjoin("PWD=", path))))
			return ;
		if (!(environ = ft_tab_replacestr(&environ, &tmp, "PWD=\0")))
			return ;
	}
}

int		ft_go_to_home(void)
{
	extern char **environ;
	int			i;
	char			path[1025];
	char			*tmp;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "HOME=", 5))
		i++;
	tmp = NULL;
	if (!(getcwd(path, 1025)) || (!(tmp = ft_strjoin("OLDPWD=", path))))
		return (-1);
	if (environ[i])
	{
		if (chdir(&environ[i][5]))
			return (put_fatal_error("HOME variable set at a wrong value\n"));
		else
		{
			if (!(environ = ft_tab_replacestr(&environ, &tmp, "OLDPWD=\0")))
				return (-1);
			if (!(tmp = ft_strdup("PWD=HOME")))
				return (-1);
			if (!(environ = ft_tab_replacestr(&environ, &tmp, "PWD=\0")))
				return (-1);
			ft_strdel(&tmp);
		}
		return (1);
	}
	return (0);
}

void	ft_change_dir(char *str)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (!str || (str[0] == '~' && !(str[1])))
	{
		if (!(i = ft_go_to_home()))
			ft_putstr_fd("Inexistant Home variable\n", 2);
		else if (i == -1)
			put_fatal_error("malloc error in ft_go_to_home");
		return ;
	}
	if (environ && (str[0] == '-' && !str[1]))
	{
		while (environ && environ[i] && ft_memcmp(environ[i], "OLDPWD", 6))
			i++;
		if (environ[i])
			ft_call_to_chdir(&environ[i][7]);
		else
			ft_putstr_fd("OLDPWD not set\n", 2);
		return ;
	}
	ft_call_to_chdir(str);
	return ;
}
