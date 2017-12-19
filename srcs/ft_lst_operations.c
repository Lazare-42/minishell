/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 07:21:24 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/19 15:05:00 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	ft_advance_lst_to(t_arg *first, t_arg **to_find, char *line)
{
	t_arg	*tmp;
	int		line_len;
	int		len_previous_arg_found;

	tmp = NULL;
	line_len = ft_strlen(line);
	len_previous_arg_found = (*to_find) ? ft_strlen((*to_find)->arg) : 0;
	tmp = (*to_find) ? *to_find : first;
	while ((tmp && tmp->arg && ft_memcmp(line, tmp->arg, line_len)) ||
			(tmp && tmp->arg && tmp->line_pos == 1))
	{
		tmp = tmp->next;
		if (len_previous_arg_found && tmp &&
				!(ft_memcmp((*to_find)->arg, tmp->arg, len_previous_arg_found)))
			tmp = tmp->next;
	}
	if (tmp)
	{
		tmp->line_pos = 1;
		*to_find = tmp;
	}
}

void	ft_clean_lst_for_line_pos(t_arg *first)
{
	while (first && first->line_pos == 1)
	{
		first = first->next;
		first->line_pos = 2;
	}
}

void	ft_retreat_lst_to(t_arg **to_find)
{
	t_arg *tmp;

	(*to_find)->line_pos = 2;
	tmp = *to_find;
	tmp = tmp->previous;
	while (tmp && tmp->line_pos != 1)
		tmp = tmp->previous;
	*to_find = tmp;
}

t_arg	*new_arg(void)
{
	t_arg	*new;

	new = NULL;
	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	if (!(new->arg = ft_strnew(0)))
	{
		ft_memdel((void*)new);
		return (NULL);
	}
	new->old_line = NULL;
	new->line_right = NULL;
	new->previous = NULL;
	new->next = NULL;
	new->line_pos = 2;
	return (new);
}
