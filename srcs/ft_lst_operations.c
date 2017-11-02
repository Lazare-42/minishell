#include "../includes/minishell.h"

void	ft_advance_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	t_arg *tmp;

	tmp = first;
	while (tmp && ft_memcmp(*line, first->arg, line_len) && tmp->line_pos == 2)
		tmp = tmp->next;
	if (tmp)
		*to_find = tmp;
}

void	ft_clean_lst_for_line_pos(t_arg *first)
{
	while (first && first->line_pos == 1)
	{
		first = first->next;
		first->line_pos = 2;
	}
}

void	ft_retreat_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	t_arg *tmp;

	tmp = first;
	while (tmp && ft_memcmp(*line, first->arg, line_len) && tmp->line_pos == 1)
		tmp = tmp->previous;
	if (tmp)
		*to_find = tmp;
}
