/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:20:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 17:24:24 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>

extern char **environ;

int		ft_change_dir(char *str)
{
	char	tmp[1025];
	int		i;

	i = 0;
	if (!str)
	{
		while (environ[i] && ft_memcmp(environ[i], "HOME=", 5))
			i++;
		chdir(&environ[i][5]);
		return (0);
	}
	if (str && str[0] != '/')
	{
		getcwd(tmp, 1024);
		ft_strcat(tmp, "/");
		ft_strcat(tmp, str);
		chdir(tmp);
		return (0);
	}
	if (!str[1])
		chdir("/");
	chdir(str);
	return (0);
}

