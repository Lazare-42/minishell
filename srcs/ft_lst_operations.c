/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 07:21:24 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 15:42:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static int	ft_define_cmp_size(t_arg *tmp, t_arg *new)
{
	int cmp_size;

	cmp_size = 0;
	if (tmp && (new)->old_line)
		cmp_size = ft_strlen((new)->old_line);
	else if (tmp && (new)->arg)
		cmp_size = ft_strlen((new)->arg);
	return (cmp_size);
}

static char	*ft_define_cmp(t_arg *tmp, t_arg *new)
{
	char *cmp;

	cmp = NULL;
	if (tmp && (new)->old_line)
		cmp = (new)->old_line;
	else if (tmp && (new)->arg)
		cmp = (new)->arg;
	return (cmp);
}

void	ft_advance_lst_to(t_arg *first, t_arg *new, t_arg **to_find, int forwrd)
{
	t_arg	*tmp;
	int		cmp_size;
	char	*cmp;
	int		previous_size;

	previous_size = (*to_find) ? ft_strlen((*to_find)->arg) : -1;
	tmp = (*to_find && forwrd) ? (*to_find)->next : first;
	tmp = (*to_find && !forwrd) ? (*to_find)->previous : tmp;
	cmp = ft_define_cmp(tmp, new);
	cmp_size = ft_define_cmp_size(tmp, new);
	while (tmp && forwrd && tmp->next && (ft_memcmp(cmp, tmp->arg, cmp_size)
				|| (int)ft_strlen(tmp->arg) == previous_size))
		tmp = tmp->next;
	while (tmp && !forwrd && (ft_memcmp(cmp, tmp->arg, cmp_size)
				|| (int)ft_strlen(tmp->arg) == previous_size))
		tmp = tmp->previous;
	if (tmp && tmp->arg && (!(ft_memcmp(cmp, tmp->arg, cmp_size))))
	{
		if (!((new)->old_line))
			(new)->old_line = (new)->arg;
		(new)->arg = ft_strdup(tmp->arg);
		*to_find = tmp;
	}
}

void	ft_listdel(t_arg **first)
{
	t_arg	*tmp;

	tmp = NULL;
	while (first && *first)
	{
		tmp = *first;
		*first = (*first)->next;
		ft_memdel((void**)&(tmp->arg));
		ft_memdel((void**)&(tmp));
	}
}

t_arg	*new_arg(void)
{
	t_arg	*new;

	new = NULL;
	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = NULL;
	new->old_line = NULL;
	new->line_right = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
