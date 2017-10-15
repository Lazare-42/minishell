#include "./include/libft.h"

void	ft_putwhites(int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_putchar(' ');
}

