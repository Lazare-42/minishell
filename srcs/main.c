# include "minishell.h"
# include <stdio.h>

extern char **environ;

int	main()
{
	int forkk;
	char	 *new;
	char	*path;
	int i;

	i = 0;
	new = NULL;

	path = NULL;
	new = getcwd(path, 1024);
	ft_putstr("This is the path (statically allocated at 1024)from getcwd  : ");
	ft_putstr(new);
	ft_putchar('\n');
	ft_putchar('\n');

	ft_putstr("This is ENVIRONMENT VARIABLES: ");
	ft_putchar('\n');
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}


	ft_putchar('\n');
	ft_putstr("This is PPID: ");
	ft_putnbr(getpid());
	forkk = fork();
	ft_putstr("\nIf this number is 0 then we are in the child process, else we are in the parent process and it is the PID number of the child \n");
	ft_putnbr(forkk);
	return (0);
}
