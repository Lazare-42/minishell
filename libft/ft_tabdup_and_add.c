/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup_and_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:02:18 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 14:08:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include <stdlib.h>

char	**ft_tabdup_and_add(char **tab, char *str, int size)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = NULL;
	if (!(new_tab = (char**)malloc(sizeof(char*) * (size + 2))))
		return (NULL);
	while (tab && tab[i])
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
			return (NULL);
		i++;
	}
	if (!(new_tab[i] = ft_strdup(str)))
		return (NULL);
	while (i <= size)
	{
		new_tab[i] = NULL;
		i++;
	}
	return (new_tab);
}
