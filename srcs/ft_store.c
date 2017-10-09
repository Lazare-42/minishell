#include "minishell.h"
#include <stdlib.h> 

static void	ft_place_element_in_tern_tree(t_arg **tmp, t_arg *new)
{
	if (ft_strcmp((*tmp)->arg, new->arg) > 0)
	{
		if ((*tmp)->left)
		{
			if (ft_strcmp(new->arg, (*tmp)->left->arg) > 0)
				ft_place_element_in_tern_tree(&(*tmp)->left, new);
			else if ((*tmp)->middle)
				ft_place_element_in_tern_tree(&(*tmp)->middle, new);
			else
				(*tmp)->middle = new;
		}
		else
			(*tmp)->left = new;
	}
	if (ft_strcmp((*tmp)->arg, new->arg) < 0)
	{
		if ((*tmp)->right)
		{
			if (ft_strcmp(new->arg, (*tmp)->right->arg) < 0)
				ft_place_element_in_tern_tree(&(*tmp)->right, new);
			else if ((*tmp)->middle)
					ft_place_element_in_tern_tree(&(*tmp)->middle, new);
			else
				(*tmp)->middle = new;
		}
		else
			(*tmp)->right = new;
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
		ft_place_element_in_tern_tree(&tmp, new);
	return (first);
}
