/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:52:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 15:43:09 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

static	char	**ft_tab_with_alias(char **values,
		char **commands, char **line_split)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (line_split[j])
	{
		i = 0;
		while (values[i])
		{
			if (!(ft_memcmp(line_split[j], values[i], ft_strlen(line_split[j])))
						&& ft_strlen(line_split[j]) == ft_strlen(values[i]))
			{
				ft_strdel(&line_split[j]);
				if (commands[i])
					line_split[j] = ft_strdup((commands[i]));
				i = 0;
				j = 0;
			}
			i++;
		}
		j++;
	}
	return (line_split);
}

static	char	*ft_used_tabdel(char **commands,
		char **values, char **line_split, char *line)
{
	if (commands)
		ft_tabdel(commands);
	if (values)
		ft_tabdel(values);
	if (line_split)
		ft_tabdel(line_split);
	return (line);
}

static	char	*ft_launch_replacement(char *line,
		char **values, char **commands, char **line_split)
{
	int		j;
	char	*space_str;

	j = 0;
	ft_memdel((void**)&line);
	space_str = NULL;
	if (!(line = ft_strnew(0)))
		return (ft_used_tabdel(commands, values, line_split, line));
	else if (!(space_str = ft_strnew(1)))
		return (ft_used_tabdel(commands, values, line_split, line));
	space_str[0] = ' ';
	line_split = ft_tab_with_alias(values, commands, line_split);
	while (line_split[j])
	{
		line = ft_strjoinfree(&line, &line_split[j], 'L');
		line = ft_strjoinfree(&line, &space_str, 'L');
		j++;
	}
	ft_memdel((void**)&space_str);
	return (ft_used_tabdel(commands, values, line_split, line));
}

static	char	*ft_malloc_for_alias(char *values_line,
		char *commands_line, char *line)
{
	char	**values;
	char	**commands;
	char	**line_split;

	values = NULL;
	commands = NULL;
	line_split = NULL;
	if (!(commands = ft_split_char(commands_line, ',')) ||
			!(values = ft_split_char(values_line, '_')) ||
			!(line_split = ft_split_whitespaces(line)))
		return (ft_used_tabdel(commands, values, line_split, line));
	return (ft_launch_replacement(line, values, commands, line_split));
}

char			*find_aliases(char *line)
{
	int		fd;
	char	*values_line;
	char	*commands_line;
	int		j;

	j = 0;
	fd = -1;
	values_line = NULL;
	commands_line = NULL;
	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt",
			O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Unable to open alias.txt\n");
		return (line);
	}
	if (!get_next_line(fd, &values_line, '\n') ||
			!get_next_line(fd, &commands_line, '\n'))
	{
		ft_putstr("Unable to read alias.txt with GNL\n");
		return (line);
	}
	close(fd);
	return (ft_malloc_for_alias(values_line, commands_line, line));
}
