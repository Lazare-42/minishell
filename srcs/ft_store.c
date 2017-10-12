#include "minishell.h"
#include <stdlib.h> 

static void	ft_place_element_in_tern_tree(t_arg *tmp, t_arg *new)
{

	t_arg *exchange;

	exchange = NULL;
	ft_putstr("\nhere is the comparison node ");
	ft_putstr((tmp)->arg);
	ft_putstr("\nhere is the new node ");
	ft_putstr(new->arg);
	if (ft_strcmp((tmp)->arg, new->arg) < 0)
	{
		ft_putstr(" to the left\n");
		if ((tmp)->left)
		{
			ft_putstr("whose value is ");
			ft_putstr(tmp->left->arg);
			if (ft_strcmp((tmp)->left->arg, new->arg) < 0)
			{
				ft_putstr(" and recurs to the left\n");
				ft_place_element_in_tern_tree((tmp)->left, new);
			}
			else if (ft_strcmp((tmp)->left->arg, new->arg) == 0)
			{
				ft_putstr("same sign, ignore");
				return ;
			}
			else if ((tmp)->middle)
			{
				if (ft_strcmp(tmp->middle->arg, new->arg) > 0)
				{
					exchange = tmp->middle;
					tmp->middle = new;
					ft_place_element_in_tern_tree(tmp->middle, exchange);
				}
				else
					ft_place_element_in_tern_tree((tmp)->middle, new);
			}
			else
			{
				ft_putstr(" and placed in the middle\n");
				(tmp)->middle = new;
				return ;
			}
		}
		else
		{
			ft_putstr("and placed to the left\n");
			(tmp)->left = new;
			return ;
		}
	}
	if (ft_strcmp((tmp)->arg, new->arg) > 0)
	{
		ft_putstr(" to the right\n");
		if ((tmp)->right)
		{
			ft_putstr("whose value is ");
			ft_putstr(tmp->right->arg);
			if (ft_strcmp((tmp)->right->arg, new->arg) > 0)
			{
				ft_putstr(" and recurs to the right\n");
				ft_place_element_in_tern_tree((tmp)->right, new);
			}
			else if (ft_strcmp((tmp)->right->arg, new->arg) == 0)
			{
				ft_putstr("same sign, ignore");
				return ;
			}
			else if ((tmp)->middle)
			{
				if (ft_strcmp(tmp->middle->arg, new->arg) < 0)
				{
					exchange = tmp->middle;
					tmp->middle = new;
					ft_place_element_in_tern_tree(tmp->middle, exchange);
				}
				else
					ft_place_element_in_tern_tree((tmp)->middle, new);
				ft_putstr(" and recurs middle\n");
			}
			else
			{
				ft_putstr(" and placed in the middle\n");
				(tmp)->middle = new;
				return ;
			}
		}
		else
		{
			ft_putstr("and placed to the right\n");
			(tmp)->right = new;
			return ;
		}
	}
	return ;
}

static t_arg	*new_arg(char *line)
{
	t_arg 	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = ft_strdup(line);
	new->left = NULL;
	new->middle = NULL;
	new->right = NULL;
	return (new);
}

t_arg	*ft_store_args(char	*line, t_arg *first)
{
	t_arg	*tmp;
	t_arg	*new;

	tmp = NULL;
	new = NULL;
	if (!first)
		return (new_arg(line));
	tmp = first;
	new = new_arg(line);
	if (new)
		ft_place_element_in_tern_tree(tmp, new);
	return (first);
}
