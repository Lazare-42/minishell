/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:26:55 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 13:51:33 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

extern	char	**environ;

static char	**ft_add_command_to_path(char **possible_path, char	*arg)
{
	int		i;
	char	*slash;

	i = 0;
	slash = "/";
	while (possible_path[i])
	{
		possible_path[i] = ft_strjoinfree(&possible_path[i], &slash, 'L');
		possible_path[i] = ft_strjoinfree(&possible_path[i], &arg, 'L');
		i++;
	}
	return (possible_path);
}

char	**ft_find_prog_path(char *arg)
{
	int		i;
	char	*tmp;
	char	**possible_program_path;

	i = 0;
	possible_program_path = NULL;
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	tmp = &environ[i][5];
	possible_program_path = ft_strsplit(tmp, ':');
	return (ft_add_command_to_path(possible_program_path, arg));
}

char	*ft_find_my_prog_path(char *arg)
{
	int		i;
	char	*path;
	char	*tmp_arg;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "PWD=", 4) != 0)
		i++;
	path = &environ[i][4];
	if (arg && arg[0] == '.' && arg[1] == '/')
	{
		tmp_arg = &arg[1];
		path = ft_strjoin(path, tmp_arg);
	}
	else if (arg)
	{
		tmp_arg = ft_strjoin("/", arg);
		path = ft_strjoinfree(&path, &tmp_arg, 'R');
	}
	return (path);
}
