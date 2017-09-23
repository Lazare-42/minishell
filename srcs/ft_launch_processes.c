#include "../includes/minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include <stdlib.h>

extern char		**environ;

static void	ft_launch_ext_command(char **arguments)
{
	int 	i;
	char 	**possible_path;
	char	*my_prog_path;
	int		forkk;

	i = 0;
	forkk = 1;
	possible_path = NULL;
	possible_path = ft_find_prog_path(arguments[0]);
	my_prog_path = NULL;
	forkk = fork();
	if (!(forkk))
	{
		while (possible_path[i] && execve(possible_path[i], arguments, environ) == -1)
			i++;
		if (!possible_path[i])
		{
			my_prog_path = ft_find_my_prog_path(arguments[0]);
			if (my_prog_path)
			{
				if (execve(my_prog_path, arguments, environ) == -1)
					ft_put_command_errors(arguments[0]);
			}
		}
		exit(0);
	}
	if (forkk)
		wait(&forkk);
	(possible_path) ? ft_tabdel(possible_path) : 0;
}

static void	ft_launch_builtin_processes(int command_number, char **arguments)
{
	if (arguments[1])
	{
		(command_number == 0) ? ft_echo(&arguments[1]): 0;
		(command_number == 1 ) ? ft_change_dir(arguments[1]) : 0;
		(command_number == 6 ) ? ft_change_dir(arguments[1]) : 0;
	}
	(command_number == 2) ? ft_sort_setenv(&arguments[1]): 0;
	(command_number == 3) ? ft_unsetenv(&arguments[1]) : 0;
	(command_number == 4) ? ft_env(&arguments[1]) : 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? exit (1): 0;
}

void	ft_launch_processes(char **arguments)
{
	int 	command_number;

	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_builtin_processes(command_number, arguments);
		else (ft_launch_ext_command(arguments));
	}
	ft_print_current_directory();
}
