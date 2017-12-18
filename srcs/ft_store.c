/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:53:48 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 21:59:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>

static	void	ft_place_element_in_tern_tree(t_arg **first, t_arg *new)
{
	new->next = *first;
	(*first)->previous = new;
	*first = new;
}

static	t_arg	*new_arg(char *line)
{
	t_arg	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = ft_strdup(line);
	new->previous = NULL;
	new->next = NULL;
	new->line_pos = 2;
	return (new);
}

static	t_arg	*ft_store_command_historic(char *line, t_arg *first)
{
	int		fd;
	char	*historic_commands;
	t_arg	*new;

	fd = -1;
	historic_commands = NULL;
	new = NULL;
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Unable to open or find the command historic file.\n");
		ft_replace_content(NULL, NULL, NULL);
		return (new_arg(line));
	}
	else
		while (get_next_line(fd, &historic_commands, '\n'))
		{
			if (!first)
				first = new_arg(historic_commands);
			new = new_arg(historic_commands);
			if (new)
				ft_place_element_in_tern_tree(&first, new);
		}
	close(fd);
	return (first);
}

t_arg			*ft_store_args(char *line, t_arg *first)
{
	t_arg	*new;
	int		fd;

	new = NULL;
	fd = -1;
	if (!first)
		return (ft_store_command_historic(line, first));
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_WRONLY);
	if (fd != -1)
	{
		lseek(fd, 0, SEEK_END);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	new = new_arg(line);
	if (new)
		ft_place_element_in_tern_tree(&first, new);
	close(fd);
	return (first);
}
