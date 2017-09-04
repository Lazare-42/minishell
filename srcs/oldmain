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

//YOU NEED TO READ MOTHAFUCKA Y U TRING TO GET IN IN ARGUMENTS LIKE A MOTHAFUCKIN STATIC FUNCTION

void	ft_launch_processes(char *str)
{
// 	"This is the child process which should stay active as the proper minishell process. It should only quit when I type exit"
	char	path[100] = "/bin/ls";
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	char	*arg[100] = {"ls", "-lR", "srcs/", NULL};

//	ft_putstr("\nthis is ARGS");
	ft_putstr(str);
	*commands = NULL;
	ft_putstr("\n");

/*
	 i = ft_recognize_command(av[0]);
	if (i != -1)
		ft_putstr(commands[i]);
	else
		ft_putstr("ERROR");
	// ft_putabs(av);
	ft_recognize_command(path);
	*/
	execve(path, arg, environ);
}

int		main()
{
	int 	forkk;
	char	path[1025];
	char	*execpath;
	char	*new;
	char	*line;
	int i;

	i = 1;
	execpath = NULL;

	new = getcwd(path, 1024);
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
	i = 1;
	while  (forkk == 0)
	{
		while (i == 1)
			i = get_next_line(1, &line);
		if (i == -1)
			ft_launch_processes(line);
	}
	/*
	else
	{
		int stat;
		wait(&stat);
		ft_putnbr(stat);
	}
	*/
	return (1);
}
