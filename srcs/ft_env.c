#include "../includes/minishell.h"

extern char **environ;

static void ft_launch_forkk(char **new_environ, char **args)
{
	ft_launch_processes(args, new_environ);
}

static void ft_env_options(char **args)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	j = 0;
	new_environ = ft_tabdup(environ, ft_tabsize(environ));
	while (args[i] && args[i][0] && args[i][0] == '-')
	{
		if (args[i][0] && args[i][0] == '-' && (!args[i][1]))
					new_environ = NULL;
		while (args[i][j])
		{
			if (args[i][j] == 'i')
					new_environ = NULL;
			j++;
		}
		i++;
	}
	j = 0;
	while (args[i] && ft_strchr(args[i], '='))
	{
		new_environ = ft_setenv(&args[i], ft_new_environ_size(&args[i], new_environ), new_environ);
		i++;
	}
	if (args[i])
		ft_launch_forkk(new_environ, &args[i]);
}

void	ft_env(char **args)
{
	if (!(args[0]))
		return (ft_put_env());
	ft_env_options(args);
}
