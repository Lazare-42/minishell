#include "../includes/minishell.h"

char	*ft_advance_lst_to(t_arg *first, char *line)
{
	t_arg	*tmp;
	int     cmp;

	tmp = first;
	cmp = 0;
	if (tmp && line)
	{
		cmp = ft_strcmp(tmp->arg, line);
		ft_putnbr(cmp);
		if (tmp->left && cmp >= 0)
			ft_advance_lst_to(tmp->left, line);
		if (tmp->right && cmp <= 0)
			ft_advance_lst_to(tmp->right, line);
		/*
		if (tmp->middle && cmp == 0)
			return (tmp->arg);
			*/
	}
	if (tmp && tmp->arg)
		return (tmp->arg);
	return (NULL);
}
