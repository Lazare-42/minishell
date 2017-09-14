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


void	ft_launch_ext_command(char **arguments)
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
		if (!possible_path[i])
			ft_put_command_errors(arguments[0]);
		exit(0);
	}
	else
		wait(&forkk);
}

void	ft_launch_processes(int command_number, char **arguments)
{
	(command_number == 0) ? ft_echo(&arguments[1]): 0;
	(command_number == 1) ? ft_change_dir(arguments[1]) : 0;
	(command_number == 2) ? ft_sort_setenv(&arguments[1]): 0;
	(command_number == 3) ? ft_putstr("unsetenv\n") : 0;
	(command_number == 4) ? ft_put_env(): 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? exit (1): 0;
}

void	ft_recognize_processes(char *str)
{
	int 	command_number;
	char	**arguments;

	if (str)
		arguments = ft_split_whitespaces(str);
	else
		return ;
	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_processes(command_number, arguments);
		else (ft_launch_ext_command(arguments));
	}
	ft_print_current_directory();
}

int	main()
{
	int		i;
	char	*line;
	t_arg	*argument_list;

	i = 1;
	argument_list = NULL;
	if (!(line = (ft_strnew(0))))
		return (1);
	ft_print_current_directory();
	while  ((line = ft_file_to_string()) || (!ft_strlen(line)))
	{
		if (ft_strchr(line, '\n'))
		{
			argument_list = ft_store_args(line, argument_list);
			ft_recognize_processes(line);
		}
		if (ft_strchr(line, '\n'))
		{
			ft_strdel(&line);
			line = ft_strnew(0);
		}
	}
	ft_strdel(&line);
}
