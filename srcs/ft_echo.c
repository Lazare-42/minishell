char extern **environ;

#include "../includes/minishell.h"

void	ft_print_corresponding_variable(char *str)
{
	size_t	i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	str++;
	if (str)
	{
		while (environ[j] && (ft_memcmp(environ[j], str, i - 1) || environ[j][i - 1] != '='))
			j++;
		if (environ[j])
			ft_putstr(&environ[j][i]);
	}
}



void	ft_parse(char **str)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j] && str[i][j] != '$')
		{
			ft_putchar(str[i][j]);
			j++;
		}
		if (str[i][j] && str[i][j] == '$')
			ft_print_corresponding_variable(&str[i][j]);
		ft_putchar(' ');
		i++;
	}
}

void	ft_echo(char **str, int quote_presence)
{
	quote_presence++;
	if (!(ft_memcmp(str[0], "-n", 2)))
		ft_parse(&str[1]);
	else
	{
		ft_parse(str);
		ft_putchar('\n');
	}
}
