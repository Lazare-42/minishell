/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 08:51:18 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 09:13:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>

void	ft_launch_processes(char *str)
{
	int 	command_number;
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	
	command_number = ft_recognize_command(str);
	if (command_number != -1)
		ft_putstr(commands[command_number]);
	else 
		ft_put_command_errors(str);
	ft_putchar('\n');
}

int	main()
{
	int i;
	char	*line;

	i = 1;
	line = NULL;
	while  (get_next_line(0, &line) == 1)
	{
		ft_launch_processes(line);
		ft_strdel(&line);
	}
}
		
