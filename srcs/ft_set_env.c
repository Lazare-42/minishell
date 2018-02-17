/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:59:50 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 15:44:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_pathlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (i);
	else
		return (0);
}

static char		*ft_add_env_var(char *env_location, char *new_env)
{
	if (env_location)
		ft_strdel(&env_location);
	env_location = ft_strdup(new_env);
	return (env_location);
}

int				ft_new_environ_size(char **args, char **environ_tocpy)
{
	int i;
	int j;

	i = 0;
	j = 0;
	j = ft_tabsize(environ_tocpy);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			j++;
		i++;
	}
	return (j + 1);
}

char			**ft_setenv(char **args, int new_environ_size,
		char **environ_tocpy)
{
	int			i;
	int			j;
	size_t		var_len;
	char		**new_env;
	extern char	**environ;

	i = -1;
	var_len = 0;
	new_env = ft_tabdup(environ_tocpy, new_environ_size);
	(environ_tocpy) ? ft_tabdel((void**)environ_tocpy) : 0;
	while (args[++i])
	{
		j = 0;
		var_len = ft_pathlen(args[i]);
		while (var_len && new_env[j] &&
		(((ft_pathlen(new_env[j]) < var_len
			|| new_env[j][var_len] != '='
			|| ft_memcmp(args[i], new_env[j], var_len)))
	|| (new_env[j] && var_len >= ft_strlen(new_env[j]))))
			j++;
		if (var_len)
			new_env[j] = ft_add_env_var(new_env[j], args[i]);
	}
	return (new_env);
}

void			ft_sort_setenv(char **args)
{
	int			i;
	extern char	**environ;

	i = 0;
	if (!args[0])
	{
		(ft_putabs(environ, '\n'));
		return ;
	}
	else if (!ft_isalpha(args[0][0]))
		ft_putstr_fd("setenv: Variable name must begin with a letter.\n", 2);
	else if (args && args[0])
		environ = ft_setenv(args, ft_new_environ_size(args, environ), environ);
}
