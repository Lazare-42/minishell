/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 00:36:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 00:39:56 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strdupfrom_free(char *str, int i)
{
	char	*dest;

	dest = NULL;
	if (str[i])
		if (!(str = ft_strdup(&str[i])))
			return (NULL);
	ft_memdel((void**)str);
	return (str);
}
