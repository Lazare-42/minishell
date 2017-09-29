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

extern	char	**environ;

int ft_check_commas(char *str)
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

void	ft_recognize_processes(char *str)
{
	char	**arguments;

	arguments = NULL;
	if (str)
	{
		arguments = ft_split_whitespaces_nokots(str);
		ft_strdel(&str);
		ft_launch_processes(arguments, environ);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int		ft_look_inside(char *line)
{
	int		comma_presence;
	t_arg	*argument_list;
	comma_presence = 0;
	argument_list = NULL;
	int i;

	i = 0;

	if (line)
	{
		ft_putchar('\r');
		argument_list = ft_store_args(line, argument_list);
		comma_presence = ft_check_commas(line);
		(!comma_presence) ? ft_recognize_processes(line) : ft_complete_command(comma_presence, line);
		return (1);
	}
	return (0);
}


int	main()
{
	char	*line;
	char	*line_cpy;

	line_cpy = NULL;
	line = NULL;
	ft_print_current_directory();
	environ = ft_tabdup(environ, ft_tabsize(environ));
	ft_file_to_string();
}
