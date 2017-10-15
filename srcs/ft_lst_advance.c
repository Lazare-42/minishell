#include "../includes/minishell.h"

void	ft_advance_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	if (first->left)
		ft_advance_lst_to(first->left, to_find, line, line_len);
	if (!ft_memcmp(*line, first->arg, line_len) && first->line_pos == 0)
	{
		*to_find = first;
	}
	if (!ft_memcmp(*line, first->arg, line_len) && first->line_pos == 1)
	{
		ft_putchar('\r');
		ft_print_current_directory();
		ft_putwhites(ft_strlen(first->arg));
	}
	if (first->right)
		ft_advance_lst_to(first->right, to_find, line, line_len);
}

void	ft_clean_lst_for_line_pos(t_arg *first)
{
	if (first->right)
		ft_clean_lst_for_line_pos(first->right);
	if (first->line_pos == 1)
		first->line_pos = 0;
	if (first->left)
		ft_clean_lst_for_line_pos(first->left);
}

void	ft_retreat_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	t_arg *tmp;

	tmp = first;
	char *coucou;
	coucou = *line;
	line_len--;
	if ((*to_find)->ante)
		(*to_find) = (*to_find)->ante;
}
