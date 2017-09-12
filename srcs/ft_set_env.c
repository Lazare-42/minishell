#include "../includes/minishell.h"

extern char** environ;

void	ft_setenv(char *name, char *value)
{
	int		i;
	char	*tmp;
	int		nbr;

	i = 0;
	nbr = 0;
	while (environ[i] && ft_memcmp(environ[i], name, 5))
		i++;
	tmp = ft_strjoin(name, "=");
	if (!environ[i])
	{
		environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
		i++;
		environ[i] = NULL;
		return ;
	}
	environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
}

void	ft_sort_setenv(char	**args)
{
	if (!args[0])
	{
		(ft_putabs(environ, '\n'));
		return ;
	}
	if (args && args[0] && args[1] && args[2])
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else if (args && args[0])
		ft_setenv(args[0], args[1]);
}
