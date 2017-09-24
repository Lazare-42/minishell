#include "../includes/minishell.h"

extern char** environ;

static size_t ft_pathlen(char *str)
{
	size_t i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (i);
	else
		return (0);
}

static char	*ft_add_env_var(char *env_location, char *new_env)
{
	if (env_location)
		ft_strdel(&env_location);
	env_location = ft_strdup(new_env);
	return (env_location);
}

char	**ft_setenv(char **args, int new_environ_size)
{
	int		i;
	int		j;
	size_t	var_len;
	char	**new_env;

	i = -1;
	var_len = 0;
	new_env = ft_tabdup(environ, new_environ_size);
	ft_tabdel(environ);
	while (args[++i])
	{
		j = 0;
		var_len = ft_pathlen(args[i]);
		while(var_len && new_env[j] && 
		(((new_env[j][var_len] != '=' || 
		   ft_memcmp(args[i], new_env[j], var_len))) || 
		(new_env[j] && var_len >= ft_strlen(new_env[j]))))
			j++;
		if (var_len)
			new_env[j] = ft_add_env_var(new_env[j], args[i]);
	}
	return (new_env);
}

void	ft_sort_setenv(char	**args)
{
	int i;

	i = 0;
	if (!args[0])
	{
		(ft_putabs(environ, '\n'));
		return ;
	}
	else if (!ft_isalpha(args[0][0]))
		ft_putstr_fd("setenv: Variable name must begin with a letter.\n", 2);
	else if (args && args[0])
		environ = ft_setenv(args, (ft_tabsize(environ) + ft_tabsize(args) + 1));
}
