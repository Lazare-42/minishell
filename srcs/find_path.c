/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:26:55 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 17:16:15 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

extern	char	**environ;

char	**ft_find_prog_path()
{
	int		i;
	char	*tmp;
	char	**possible_program_path;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	tmp = &environ[i][5];
	ft_putstr(environ[i]);
	possible_program_path = ft_strsplit(tmp, ':');
	return (possible_program_path);
}
