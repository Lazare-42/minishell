/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:53:48 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/19 15:02:47 by lazrossi         ###   ########.fr       */
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

static	t_arg	*ft_store_command_historic(t_arg *first)
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
		return (new_arg());
	}
	else
		while ((new = new_arg()) && get_next_line(fd, &new->arg, '\n'))
		{
			if (!first)
				first = new;
			ft_place_element_in_tern_tree(&first, new);
		}
	close(fd);
	return (first);
}

t_arg			*ft_store_args(t_arg *first, t_arg *new_arg)
{
	int		fd;

	fd = -1;
	if (!first)
		return (ft_store_command_historic(first));
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_WRONLY);
	if (fd != -1)
	{
		lseek(fd, 0, SEEK_END);
		write(fd, new_arg->arg, ft_strlen(new_arg->arg));
		write(fd, "\n", 1);
	}
	ft_place_element_in_tern_tree(&first, new_arg);
	close(fd);
	return (first);
}
