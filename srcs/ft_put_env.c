#include "../includes/minishell.h"

extern char **environ;

void	ft_put_env()
{
	ft_putabs(environ, '\n');
}
