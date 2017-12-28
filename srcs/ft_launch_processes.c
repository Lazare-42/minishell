/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_processes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:59:40 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 12:45:00 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

void	ft_ex_myprog_or_exit(char **arguments,
		char **environ)
{
	if (execve(arguments[0], arguments, environ) == -1)
		ft_put_command_errors(arguments[0]);
}

static void	ft_launch_ext_command(char **arguments)
{
	int				i;
	char			**possible_path;
	int				forkk;
	extern char		**environ;

	i = 0;
	forkk = 1;
	possible_path = NULL;
	if (!(forkk = fork()))
	{
		if (environ[0])
			possible_path = ft_find_prog_path(arguments[0], environ);
		if (!possible_path && environ[0])
			ft_put_command_errors(arguments[0]);
		while (possible_path && possible_path[i] && execve(possible_path[i],
					arguments, environ) == -1)
			i++;
		if (!(possible_path))
			execve(arguments[0], arguments, NULL); 
		if (possible_path && !possible_path[i])
			ft_ex_myprog_or_exit(arguments, environ);
		exit(0);
	}
	if (forkk)
		wait(&forkk);
	(possible_path) ? ft_tabdel(possible_path) : 0;
}

static void	ft_launch_builtin_processes(int command_number, char **arguments, t_arg **first)
{
	if (arguments[1])
	{
		(command_number == 0) ? ft_echo(&arguments[1]) : 0;
		(command_number == 6) ? ft_change_dir(arguments[1]) : 0;
		(command_number == 7) ? ft_new_alias(&arguments[1]) : 0;
	}
	(command_number == 1) ? ft_change_dir(arguments[1]) : 0;
	(command_number == 2) ? ft_sort_setenv(&arguments[1]) : 0;
	(command_number == 3) ? ft_unsetenv(&arguments[1]) : 0;
	(command_number == 4) ? ft_env(&arguments[1]) : 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? ft_listdel(first) : 0;
	(command_number == 5) ? exit(1) : 0;
}

void		ft_launch_processes(char **arguments, t_arg **first)
{
	int	command_number;

	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_builtin_processes(command_number, arguments, first);
		else
			(ft_launch_ext_command(arguments));
	}
	ft_replace_content(NULL);
}
