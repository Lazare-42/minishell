#include "libft/include/libft.h"

extern char **environ;

int main(int ac, char **av)
{
	(void)ac;
	char **newtab;

	newtab = NULL;
	newtab = ft_tabdup(av, ft_tabsize(av));
	ft_putabs(newtab, '\n');
	ft_tabdel(newtab);
	return (0);
}
