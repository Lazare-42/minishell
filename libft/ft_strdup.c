/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 00:20:27 by lazrossi          #+#    #+#             */
/*   Updated: 2017/04/21 15:58:11 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "include/libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(*str) * (ft_strlen(src) + 1))))
		return (0);
	str[ft_strlen(src)] = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
