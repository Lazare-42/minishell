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
		arguments = ft_split_whitespaces(str);
		ft_launch_processes(arguments);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int	main()
{
	char	*line;
	char	*line_cpy;
	t_arg	*argument_list;
	int		comma_presence;

	argument_list = NULL;
	line_cpy = NULL;
	line = NULL;
	comma_presence = 0;
	ft_print_current_directory();
	while  ((line = ft_file_to_string()) || (!ft_strlen(line)))
	{
		if (ft_strchr(line, '\n'))
		{
			argument_list = ft_store_args(line, argument_list);
			comma_presence = ft_check_commas(line);
			(!comma_presence) ? ft_recognize_processes(line) : ft_complete_command(comma_presence, line);
			ft_strdel(&line);
		}
	}
}
