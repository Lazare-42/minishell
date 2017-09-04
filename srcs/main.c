/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:59:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/04 16:57:27 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>

extern char **environ;

void ft_launch_processes(int PID)
{
// 	"This is the child process which should stay active as the proper minishell process. It should only quit when I type exit"
	int i;
	char path[100] = "/bin/ls";
	char *arg[100] = {"ls", "-lR", "srcs/", NULL};

	i = 1;
	ft_putstr("\nIf this number is 0 then we are in the child process \n");
	ft_putnbr(PID);
	ft_recognize_command(path);
	execve(path, arg, environ);
}

int	main()
{
	int 	forkk;
	char	path[1025];
	char	*execpath;
	int i;

	i = 0;
	execpath = NULL;

	getcwd(path, 1024);
	ft_putstr("This is the path (statically allocated at 1024)from getcwd. This path is useful for chdir() because there is no system call t know in which process we're at : \n");
	ft_putchar('\n');

	ft_putstr("This is ENVIRONMENT VARIABLES: ");
	ft_putchar('\n');
	while (environ[i])
	{
		if (ft_memcmp(environ[i], "PATH=", 5) == 0)
			execpath = environ[i];
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}


	ft_putchar('\n');
	ft_putstr("This is execpath  ");
	ft_putstr(execpath);

	ft_putchar('\n');
	ft_putstr("This is PID: ");
	ft_putnbr(getpid());
	forkk = fork();
	if (forkk == 0)
		ft_launch_processes(forkk);
	else
	{
		int stat;
		wait(&stat);
		ft_putnbr(stat);
	}
	return (1);
}
