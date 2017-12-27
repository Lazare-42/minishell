/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_dup_add_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:31:39 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/22 16:03:17 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include <stdlib.h>

char	**ft_tab_dup_add_free(char **tab, char *str)
{
	int		i;
	int		size;
	char	**new_tab;

	i = 0;
	new_tab = NULL;
	size = 2;
	size = (tab) ? size += ft_tabsize(tab) : 2;
	if (!(new_tab = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	new_tab[size - 1] = NULL;
	i = 0;
	while (tab && tab[i])
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
			return (NULL);
		i++;
	}
	if (!(new_tab[i] = ft_strdup(str)))
		return (NULL);
	ft_memdel((void**)tab);
	return (new_tab);
}

