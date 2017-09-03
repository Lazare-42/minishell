/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:46:56 by lazrossi          #+#    #+#             */
/*   Updated: 2017/04/25 18:38:42 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_separations(char *str, int c)
{
	int	i;
	int	b;
	int	n;

	n = 0;
	i = 0;
	b = 1;
	if (!*str)
		return (0);
	while (str[i])
	{
		if (b == 0 && str[i] == c)
			b = 1;
		else if (b == 1 && str[i] != c)
		{
			n++;
			b = 0;
		}
		i++;
	}
	return (n);
}

static int	ft_str_csize(char *str, int c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i] && str[i] != c)
	{
		++i;
		++n;
	}
	return (n);
}

static char	**ft_fill(char *str, char **tab, int c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			if (!(tab[j] = (char*)malloc(sizeof(char) \
							* (ft_str_csize(&str[i], c) + 1))))
				return (NULL);
			k = 0;
			while (str[i] && str[i] != c)
				tab[j][k++] = str[i++];
			tab[j++][k] = '\0';
		}
	}
	tab[j] = NULL;
	return (tab);
}

char		**ft_strsplit(char const *str, char c)
{
	char **tab;

	if (!str)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(*tab) \
					* (ft_count_separations((char*)str, c) + 1))))
		return (NULL);
	tab[ft_count_separations((char*)str, c)] = NULL;
	if (!(tab = ft_fill((char*)str, tab, c)))
		return (NULL);
	return (tab);
}
