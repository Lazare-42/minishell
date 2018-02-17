#include "./../includes/libft.h"

void	debug(void)
{
	static int nbr = 0;

	nbr++;
	ft_putstr("Debug");
	ft_putnbr(nbr);
	ft_putchar('\n');
}
