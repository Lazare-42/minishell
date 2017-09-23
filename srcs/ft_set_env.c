#include "../includes/minishell.h"

extern char** environ;

char	**ft_setenv(char *name, char *value)
{
	int		i;
	char	*tmp;
	int		nbr;
	int		name_len;
	char	**new_environ;


	i = 0;
	nbr = 0;
	name_len = ft_strlen(name);
	ft_putnbr(name_len);
	new_environ = ft_tabdup(environ);
	ft_putabs(new_environ, '\n');
	while (new_environ[i] && ft_memcmp(new_environ[i], name, name_len))
		i++;
	tmp = ft_strjoin(name, "=");
	if (!new_environ[i])
	{
		new_environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
		i++;
		new_environ[i] = NULL;
		return (new_environ);
	}
	new_environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
	return (new_environ);
}

void	ft_sort_setenv(char	**args)
{
	if (!args[0])
		return(ft_put_env());
	else if (!ft_isalpha(args[0][0]))
		ft_putstr_fd("setenv: Variable name must begin with a letter.\n", 2);
	else if (args && args[0] && args[1] && args[2])
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else if (args && args[0])
		ft_setenv(args[0], args[1]);
}
