/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:19:37 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 12:19:38 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	debug(void)
{
	static int nbr = 0;

	nbr++;
	ft_putstr("Debug");
	ft_putnbr(nbr);
	ft_putchar('\n');
}
