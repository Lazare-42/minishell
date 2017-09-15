#include "../includes/minishell.h"

extern char **environ;

void	ft_echo(char **str)
{
	int		newline;
	char	**tmp;
	int		i;

	newline = 1;
	tmp = str;
	if (*str && !(ft_memcmp(str[0], "-n", 2)))
	{
		newline = 0;
		tmp = &str[1];
	}
	if (*tmp && *tmp[0] == "\'" || *tmp[0] == "\"")
	{
		while 
		
}
