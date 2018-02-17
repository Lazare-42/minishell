#include "./../includes/libft.h"

int		ft_put_fatal_error(char *str)
{
	ft_putstr_fd("Exiting for the following reason : ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
