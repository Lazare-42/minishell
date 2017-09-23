#include "include/libft.h"

int	ft_str_isalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
