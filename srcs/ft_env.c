#include "../includes/minishell.h"

extern char **environ;

static void ft_launch_forkk(char **new_environ, int launch_setenv)
{
	if (launch_setenv && new_environ)
	{
	}
}

static void ft_env_options(char **args)
{
	int		i;
	int		j;
	int		launch_setenv;
	char	**new_environ;

	i = 0;
	j = 0;
	new_environ = environ;
	launch_setenv = 0;
	while (args[i] && args[i][0] && args[i][0] == '-')
	{
		if (args[i][0] && args[i][0] == '-' && (!args[i][1]))
					new_environ = NULL;
		while (args[i][j])
		{
			if (args[i][j] == 'i')
					new_environ = NULL;
			if (args[i][j] == 'u')
				launch_setenv = 1;
			j++;
		}
		i++;
	}
	ft_launch_forkk(new_environ, launch_setenv);
}

void	ft_env(char **args)
{
	int		i;

	i = 0;
	if (!(args[0]))
		return (ft_put_env());
	ft_env_options(args);
}
