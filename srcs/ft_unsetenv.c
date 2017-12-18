/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:51:33 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 21:53:32 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_del_one_environ_var(char *str)
{
	int			i;
	int			to_del;
	extern char **environ;

	i = 0;
	to_del = 1;
	while (environ[i] && ft_strcmp(str, environ[i]))
		i++;
	while (environ[i])
	{
		if (to_del)
		{
			ft_strdel(&environ[i]);
			to_del = 0;
		}
		environ[i] = environ[i + 1];
		i++;
	}
}

void			ft_unsetenv(char **str)
{
	int			i;
	int			j;
	int			len;
	extern char **environ;

	i = 0;
	len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		j = 0;
		while (environ[j] && (environ[j][len] != '='
					|| ft_memcmp(environ[j], str[i], len - 1)))
			j++;
		if (environ[j])
			ft_del_one_environ_var(environ[j]);
		else
		{
			ft_putstr_fd("unsetenv: no environement variable named \"", 2);
			ft_putstr_fd(str[i], 2);
			ft_putchar_fd('\"', 2);
			ft_putchar('\n');
		}
		i++;
	}
}
