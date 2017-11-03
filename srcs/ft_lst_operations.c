#include "../includes/minishell.h"

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
