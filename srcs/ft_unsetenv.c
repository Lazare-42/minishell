extern char **environ;

#include "../includes/minishell.h"

static void	ft_del_one_environ_var(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (environ[i] && ft_strcmp(str, environ[i]))
		i++;
	while (environ[i])
	{
		environ[i] = environ[i + 1];
		i++;
	}
}

void	ft_unsetenv(char **str)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		j = 0;
		while(environ[j] && (environ[j][len] != '=' || ft_memcmp(environ[j], str[i], len - 1)))
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

