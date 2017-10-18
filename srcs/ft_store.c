#include "minishell.h"
#include <stdlib.h> 

static void	ft_place_element_in_tern_tree(t_arg *tmp, t_arg *new, size_t nw_len)
{
	if (ft_strcmp((tmp)->arg, new->arg) < 0)
	{
		if ((tmp)->left)
				ft_place_element_in_tern_tree((tmp)->left, new, nw_len);
		else
			(tmp)->left = new;
	}
	else if (ft_memcmp(tmp->arg, new->arg, ft_strlen(new->arg)))
	{
		if ((tmp)->right)
				ft_place_element_in_tern_tree((tmp)->right, new, nw_len);
		else
			(tmp)->right = new;
	}
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
	new->line_pos = 2;
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
		ft_place_element_in_tern_tree(tmp, new, ft_strlen(new->arg));
	return (first);
}
