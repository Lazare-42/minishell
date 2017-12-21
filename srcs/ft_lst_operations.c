/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 07:21:24 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 18:20:24 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	ft_advance_lst_to(t_arg *first, t_arg *new, t_arg **to_find)
{
	t_arg	*tmp;
	int		cmp_size;
	char	*cmp;

	if (new->old_line)
	{
		ft_putstr("\nWTF : you have old line ");
		ft_putstr(new->old_line);
		ft_putchar('\n');
	}
	tmp = (*to_find) ? (*to_find)->next : first;
	if (tmp && (new)->old_line)
	{
		cmp = (new)->old_line;
		cmp_size = ft_strlen((new)->old_line);
	}
	else if (tmp && (new)->arg)
	{
		cmp = (new)->arg;
		cmp_size = ft_strlen((new)->arg);
	}
	while (tmp && tmp->next && (ft_memcmp(cmp, tmp->arg, cmp_size)))

		tmp = tmp->next;
	if (tmp && tmp->arg && (!(ft_memcmp(cmp, tmp->arg, cmp_size))))
	{
		if (!((new)->old_line))
			(new)->old_line = (new)->arg;
		(new)->arg = tmp->arg;
		*to_find = tmp;
	}
}

void	ft_retreat_lst_to(t_arg **to_find)
{
	t_arg *tmp;

	tmp = *to_find;
	tmp = tmp->previous;
	while (*to_find->previous && ft_memcmp((*to_find)->arg, /
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
	return (new);
}
