#include "../includes/minishell.h"

void	ft_echo(char **str, int quote_presence)
{
	quote_presence++;
	if (str)
	{
		if (!(ft_memcmp(str[0], "-n", 2)))
			ft_putabs(&str[1], ' ');
		else
		{
			ft_putabs(str, ' ');
			ft_putchar('\n');
		}
	}
}
