/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:37:30 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 13:20:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

static void ft_print_git()
{
	DIR				*dir;
	struct dirent	*dent;

	if ((dir = opendir(".")))
	{
		while (dir && (dent = readir(dir)))
		{
			if (dent->d_name[0] == '.')
			{
				if (!ft_memcmp(dent->d_name, ".git", 4))
				{
					closedir(dir);
					opendir(
	}
}

void		ft_print_current_directory()
{
	char	path[1025];
	char 	*tmp;
	int		i;

	i = 0;
	tmp = getcwd(path, 1024);
	if (tmp)
		i = ft_strlen(tmp);
	if (i > 1)
		i--;
	while (tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	ft_putstr("\e[0;91m");
	if (tmp)
		ft_putstr(&tmp[i]);
	ft_putchar(' ');
	ft_putstr("\e[0m");
	ft_print_git();
}
