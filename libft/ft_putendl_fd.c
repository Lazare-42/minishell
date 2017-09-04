/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 11:59:29 by lazrossi          #+#    #+#             */
/*   Updated: 2017/04/24 12:00:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	int i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	ft_putchar_fd('\n', fd);
}
