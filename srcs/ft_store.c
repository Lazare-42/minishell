#include "minishell.h"
#include <stdlib.h> 

static void	ft_place_element(t_arg **tmp, t_arg *new)
{
	if (ft_strcmp((*tmp)->arg, new->arg) > 0)
	{
		if (!((*tmp)->left))
			(*tmp)->left = new;
		else
			ft_place_element(&((*tmp)->left), new);
	}
	if (ft_strcmp((*tmp)->arg, new->arg) < 0)
	{
		if (!((*tmp)->right))
			(*tmp)->right = new;
		else
			ft_place_element(&(*tmp)->right, new);
	}
	if (ft_strcmp((*tmp)->arg, new->arg) == 0)
	{
		if (!((*tmp)->middle))
			(*tmp)->middle = new;
		else
			ft_place_element(&(*tmp)->middle, new);
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
		ft_place_element(&tmp, new);
	return (first);
}
