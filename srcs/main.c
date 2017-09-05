/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 08:51:18 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 17:14:06 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>

extern	char	**environ;

int		ft_launch_ext_command(char *arg)
{
	int i;
	char **possible_path;

	i = 0;

	arg = NULL;
	possible_path = ft_find_prog_path();
	ft_putabs(possible_path);
//	execve(path, arg, environ);
	return (-1);
}


void	ft_launch_processes(int command_number)
{
	(command_number == 0) ? ft_putstr("echo") : 0;
	(command_number == 1) ? ft_putstr("cd") : 0;
	(command_number == 2) ? ft_putstr("setenv") : 0;
	(command_number == 3) ? ft_putstr("unsetenv") : 0;
	(command_number == 4) ? ft_putstr("env") : 0;
	(command_number == 5) ? ft_putstr("exit") : 0;
}

void	ft_recognize_processes(char *str)
{
	ft_print_current_directory();
	int 	command_number;
//	char	*builtin_commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	//char	*extern_commands[] = {"ls", "pwd", "rm", "mkdir", "make", "vim", NULL};
	
	if ((command_number = ft_recognize_builtin_command(str)) != -1)
		ft_launch_processes(command_number);
	else if ((command_number = ft_launch_ext_command(str)) != -1)
		return ;
	//else 
	//	ft_put_command_errors(str);
//	ft_putchar('\n');
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
		
