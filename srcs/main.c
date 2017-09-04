# include "../libft/include/libft.h"

int	main()
{
	int i;
	char	*line;

	i = 1;
	line = NULL;
	while  (get_next_line(0, &line) == 1)
	{
		ft_putstr(line);
		ft_putchar('\n');
		ft_strdel(&line);
	}
}
		
