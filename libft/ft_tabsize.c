#include "include/libft.h"

int	ft_tabsize(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
