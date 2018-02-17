/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:04:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 21:25:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

static char		**ft_add_command_to_path(char **possible_path, char *arg)
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

char			**ft_find_prog_path(char *arg, char **environ)
{
	int			i;
	char		*tmp;
	char		**possible_program_path;

	i = 0;
	possible_program_path = NULL;
	while (environ[i] && environ && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	if (!(environ[i]))
		return (NULL);
	tmp = &environ[i][5];
	possible_program_path = ft_strsplit(tmp, ':');
	return (ft_add_command_to_path(possible_program_path, arg));
}
