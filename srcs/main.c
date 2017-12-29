/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 16:16:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "minishell.h"

int		ft_check_commas(char *str)
{
	int i;
	int	comma_presence;

	i = 0;
	comma_presence = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (2);
	return (0);
}

void	ft_recognize_processes(char *str, t_arg **first)
{
	char			**arguments;

	arguments = NULL;
	if (str)
	{
		if (!(arguments = ft_split_whitespaces_nokots(str)))
			return ;
		ft_launch_processes(arguments, first, NULL);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int		ft_look_inside(char *line, t_arg **first)
{
	int		comma_presence;

	comma_presence = 0;
	if (line)
	{
		comma_presence = ft_check_commas(line);
		(!comma_presence) ? ft_recognize_processes(line, first)
			: ft_complete_command(comma_presence, &line, first);
		return (1);
	}
	return (0);
}

int		main(void)
{
	extern char **environ;

	if (!(environ = ft_tabdup(environ, ft_tabsize(environ))))
		return (0);
	ft_file_to_string();
}
