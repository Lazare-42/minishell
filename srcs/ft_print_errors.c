/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:09:39 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 09:12:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"

void	ft_put_command_errors(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '	')
	{
		ft_putchar_fd(str[i], 2);
		i++;
	}
	ft_putchar('\n');
}

