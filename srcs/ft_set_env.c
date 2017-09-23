#include "../includes/minishell.h"

extern char** environ;

int		ft_pathlen(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (i);
	else
		return (0);
}

char	**ft_setenv(char **args, int new_environ_size)
{
	int		i;
	int		j;
	int		path_len;
	char	**new_env;

	i = 0;
	path_len = 0;
	new_env = ft_tabdup(environ, new_environ_size);
	while (args[i])
	{
		j = 0;
		path_len = ft_pathlen(args[i]);
		while(path_len && new_env[j] && (new_env[j][path_len] != '=' || ft_memcmp(args[i], new_env[j], path_len)))
			j++;
		if (ft_strchr(args[i], '='))
			new_env[j] = ft_strdup(args[i]);
		i++;
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
		environ = ft_setenv(args, ft_tabsize(environ) + ft_tabsize(args) + 1);
}
