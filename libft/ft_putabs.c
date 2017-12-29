/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:29:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 11:40:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_putabs(char **str, char separator)
{
	int i;

	i = 2;
	while (str && str[i])
	{
		ft_putstr(str[i]);
		ft_putchar(separator);
		i++;
	}
}
