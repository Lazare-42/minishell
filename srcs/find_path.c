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

	i = 0;
	while (possible_path[i])
	{
		possible_path[i] = ft_strjoin(possible_path[i], "/");
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
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	tmp = &environ[i][5];
	possible_program_path = ft_strsplit(tmp, ':');
	return (ft_add_command_to_path(possible_program_path, arg));
}

