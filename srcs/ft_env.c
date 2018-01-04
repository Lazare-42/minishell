/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 18:38:34 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 15:44:24 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_launch_forkk(t_arg **first, char **args, char **environ)
{
	ft_launch_processes(args, first, environ);
}

static void		ft_env_options(char **args, t_arg **first)
{
	int				i;
	int				j;
	char			**new_environ;
	extern	char	**environ;

	i = -1;
	j = -1;
	new_environ = ft_tabdup(environ, ft_tabsize(environ));
	while (args[++i] && args[i][0] && args[i][0] == '-')
	{
		if (args[i][0] && args[i][0] == '-' && (!args[i][1]))
			new_environ = NULL;
		while (args[i][++j])
		{
			if (args[i][j] == 'i')
				new_environ = NULL;
		}
	}
	while (args[i] && ft_strchr(args[i], '='))
	{
		new_environ = ft_setenv(&args[i], ft_new_environ_size(&args[i],
					new_environ), new_environ);
		i++;
	}
	(args[i]) ? ft_launch_forkk(first, &args[i], new_environ) : ft_tabdel(new_environ);
}

void			ft_env(char **args, t_arg **first)
{
	if (!(args[0]))
		return (ft_put_env());
	ft_env_options(args, first);
}
