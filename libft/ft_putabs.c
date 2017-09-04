#include "include/libft.h"

void	ft_putabs(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putstr(*str);
		i++;
	}
}
