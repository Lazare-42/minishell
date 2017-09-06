/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 08:51:18 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 14:19:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include <stdlib.h>

extern	char	**environ;


int		ft_launch_ext_command(char **arguments)
{
	int i;
	char **possible_path;
	int		forkk;

	i = 0;
	forkk = 1;
	possible_path = ft_find_prog_path(arguments[0]);
	forkk = fork();
	if (!(forkk))
	{
		while (possible_path[i] && execve(possible_path[i], arguments, environ) == -1)
			i++;
		exit(0);
	}
	else
		wait(&forkk);
	if (!possible_path[i])
		return (-1);
	return (0);
}


void	ft_launch_processes(int command_number, char **arguments)
{
	(command_number == 0) ? ft_putstr("echo") : 0;
	(command_number == 1) ? ft_change_dir(arguments[1]) : 0;
	(command_number == 2) ? ft_putstr("setenv") : 0;
	(command_number == 3) ? ft_putstr("unsetenv") : 0;
	(command_number == 4) ? ft_putstr("env") : 0;
	(command_number == 5) ? ft_putstr("exit") : 0;
}

void	ft_recognize_processes(char *str)
{
	int 	command_number;
	char	**arguments;

	arguments = ft_split_whitespaces(str);
	if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_processes(command_number, arguments);
	else if ((command_number = ft_launch_ext_command(arguments)) == -1)
		ft_put_command_errors(arguments[0]);
	ft_print_current_directory();
}

int	main()
{
	int i;
	char	*line;

	i = 1;
	line = NULL;
	ft_print_current_directory();
	while  (get_next_line(0, &line, '\n') == 1)
	{
		ft_recognize_processes(line);
		ft_strdel(&line);
	}
}
