/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:37:30 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 11:09:49 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

void	ft_print_current_directory()
{
	char	path[1025];
	char 	*tmp;
	int		i;

	tmp = getcwd(path, 1024);
	i = ft_strlen(tmp);
	i--;
	while (tmp[i] != '/')
		i--;
	i++;
	ft_putstr("\e[0;96m");
	ft_putstr(&tmp[i]);
	ft_putchar(' ');
	ft_putstr("\e[0m");
}
