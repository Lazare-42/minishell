#include "../includes/minishell.h"

t_arg	*ft_advance_lst_to(t_arg *first, char *line)
{
	t_arg	*tmp;
	char	*cpy;
	int		cpy_size;
	int     cmp;

	tmp = first;
	cmp = 0;
	cpy_size = ft_strlen(line);
	ft_putnbr(cpy_size);
	ft_putstr(line);
	if (tmp && line)
	{
		cpy = ft_strnew(cpy_size + 1);
		cpy = ft_memcpy(cpy, tmp->arg, cpy_size + 1);
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putstr("\nhere comes cpy");
		ft_putchar('\n');
		ft_putstr(cpy);
		ft_putstr("\nhere was cpy");
		ft_putchar('\n');
		if (ft_strcmp(line, cpy) == 0)
		{
			ft_putstr("\nidentical");
			return (tmp);
		}
		else if (ft_strcmp(line, cpy) > 0)
		{
			if (tmp->left)
			{
				cpy = ft_memcpy(cpy, tmp->left->arg, cpy_size);
				if (ft_strcmp(line, cpy) >= 0)
				{
					ft_putstr("\ngo left");
					ft_advance_lst_to(tmp->left, line);
				}
				else if (tmp->middle)
				{
					ft_putstr("\ngo middle");
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

				ft_putstr("\ngo right");
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
	else
		ft_putstr("WTF");
	return (NULL);
}
