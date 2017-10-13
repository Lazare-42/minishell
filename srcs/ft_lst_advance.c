#include "../includes/minishell.h"

void	ft_advance_lst_to(t_arg *first, char **line, int line_len)
{

	if (first->right)
		ft_advance_lst_to(first->right, line, line_len);
	if (!ft_memcmp(*line, first->arg, line_len))
	{
		ft_strdel(line);
		*line = ft_strdup(first->arg);
		return ;
	}
	if (first->left)
		ft_advance_lst_to(first->left, line, line_len);
	/*
	t_arg	*tmp;
	int     cmp;

	tmp = NULL;
	tmp = first;
	cmp = 0;
	cmp = ft_strlen(line);
	ft_putstr(first->arg);
	if (ft_memcmp(tmp->arg, line,  cmp) == 0)
		return (tmp);
	else if (tmp && line)
	{
		if (ft_memcmp(line, tmp->arg, cmp) > 0)
		{
			if (tmp->left)
			{
				ft_putstr("go_left\n");
				ft_advance_lst_to(tmp->left, line);
			}
		}
		else if (ft_memcmp(line, tmp->arg, cmp) < 0)
		{
			if (tmp->right)
			{
				ft_putstr("go_right");
				ft_advance_lst_to(tmp->right, line);
			}
		}
	}
	return (tmp);
	*/
}
