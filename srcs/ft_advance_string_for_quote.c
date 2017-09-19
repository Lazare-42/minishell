#include "../includes/minishell.h"

char	*ft_advance_string_for_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] != '\'')
				i++;
			return (&str[i]);
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i] != '\"')
				i++;
			return (&str[i]);
		}
		i++;
	}
	return (str);
}
