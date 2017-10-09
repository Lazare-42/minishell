#include "../includes/minishell.h"

t_arg	*ft_advance_lst_to(t_arg *first, char *line)
{
	t_arg	*tmp;
	char	*cpy;
	int		cpy_size;
	int     cmp;

	tmp = first;
	cmp = 0;
	cpy = NULL;
	cpy_size = ft_strlen(line);
	if (tmp)
	{
		cpy = ft_memcpy(cpy, tmp->arg, cpy_size);
		if (ft_strcmp(line, cpy) == 0)
			return (tmp);
		else if (ft_strcmp(line, cpy) > 0)
		{
			if (tmp->left)
			{
				cpy = ft_memcpy(cpy, tmp->left->arg, cpy_size);
				if (ft_strcmp(line, cpy) >= 0)
					ft_advance_lst_to(tmp->left, line);
				else if (tmp->middle)
					ft_advance_lst_to(tmp->left, line);
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
				cpy = ft_memcpy(cpy, tmp->right->arg, cpy_size);
				if (ft_strcmp(line, cpy) <= 0)
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
