#include "../includes/minishell.h"

char	*ft_advance_lst_to(t_arg *first, char *line)
{
	t_arg	*tmp;

	tmp = first;
	if (tmp && line)
	{
		ft_putstr("coucou");
		if (tmp->left && ft_strcmp(tmp->left->arg, line) > 0)
			ft_advance_lst_to(tmp->left, line);
		if (tmp->right && ft_strcmp(tmp->right->arg, line) < 0)
			ft_advance_lst_to(tmp->right, line);
		if (tmp->middle && ft_strcmp(tmp->middle->arg, line) == 0)
			ft_advance_lst_to(tmp->middle, line);
	}
	if (tmp && tmp->arg)
		return (tmp->arg);
	return (NULL);
}
