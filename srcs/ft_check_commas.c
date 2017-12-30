/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_commas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 21:37:58 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/30 21:38:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_check_commas(char *str)
{
	int i;
	int	comma_presence;

	i = 0;
	comma_presence = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (2);
	return (0);
}
