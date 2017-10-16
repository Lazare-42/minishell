#include "../includes/minishell.h"

void	ft_advance_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	if (first->left)
		ft_advance_lst_to(first->left, to_find, line, line_len);
	if (!ft_memcmp(*line, first->arg, line_len) && first->line_pos == 2)
		*to_find = first;
	if (first->right)
		ft_advance_lst_to(first->right, to_find, line, line_len);
}

void	ft_clean_lst_for_line_pos(t_arg *first)
{
	if (first->right)
		ft_clean_lst_for_line_pos(first->right);
	if (first->line_pos == 1)
		first->line_pos = 2;
	if (first->left)
		ft_clean_lst_for_line_pos(first->left);
}

void	ft_retreat_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	if (first->right)
		ft_retreat_lst_to(first->right, to_find, line, line_len);
	if (!ft_memcmp(*line, first->arg, line_len) && first->line_pos == 1)
		*(to_find) = first;
	if (first->left)
		ft_retreat_lst_to(first->left, to_find, line, line_len);
}
