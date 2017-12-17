/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree_str_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 16:18:54 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/17 16:20:24 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include <stdlib.h>

char	*ft_strjoinfree_str_char(char **s1, char s2)
{
	char *str;

	str = NULL;
	if (!(str = ft_strjoin(*s1, &s2)))
		return (NULL);
	ft_memdel((void*)s1);
	return (str);
}
