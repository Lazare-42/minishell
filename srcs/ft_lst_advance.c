#include "../includes/minishell.h"

t_arg	*ft_advance_lst_to(t_arg *first, char *line)
{
	t_arg	*tmp;
	int     cmp;

	tmp = first;
	cmp = 0;
	if (tmp && line)
	{
		ft_putchar('\n');
		ft_putstr(tmp->arg);
		cmp = ft_strlen(line);
		if (ft_memcmp(line, tmp->arg, cmp) == 0)
			return (tmp);
		else if (ft_memcmp(line, tmp->arg, cmp) > 0)
		{
			if (tmp->left)
			{
				if (ft_memcmp(line, tmp->arg, cmp) >= 0)
				{
					ft_advance_lst_to(tmp->left, line);
				}
				else if (tmp->middle)
				{
					ft_advance_lst_to(tmp->left, line);
				}
				else
					return (NULL);
			}
			else
				return (NULL);
		}
		else if (tmp->right)
		{
			if (tmp->right)
			{
				if (ft_memcmp(line, tmp->arg, cmp) <= 0)
					ft_advance_lst_to(tmp->right, line);
				else if (tmp->middle)
					ft_advance_lst_to(tmp->left, line);
				else
					return (NULL);
			}
		}
	}
	return (NULL);
}
