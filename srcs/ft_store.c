#include "minishell.h"
#include <stdlib.h> 
#include <fcntl.h>

static int right = 0;

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

static t_arg	*ft_store_command_historic(char *line, t_arg *first)
{
	int		fd;
	char	*historic_commands;
	t_arg	*tmp;
	t_arg	*new;	

	fd = -1;
	historic_commands = NULL;
	new = NULL;
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_RDWR);
	if (fd == -1)
	{
		ft_putstr("Unable to open or find the command historic file\n");
		return (new_arg(line));
	}
	else while (get_next_line(fd, &historic_commands, '\n'))
	{
		if (!first)
			first = new_arg(historic_commands);
		tmp = first;
		new = new_arg(historic_commands);
		if (new)
			ft_place_element_in_tern_tree(tmp, new, ft_strlen(new->arg));
	}
	return (first);
}

t_arg	*ft_store_args(char	*line, t_arg *first)
{
	t_arg	*tmp;
	t_arg	*new;

	tmp = NULL;
	new = NULL;
	if (!first)
		return (ft_store_command_historic(line, first));
	tmp = first;
	new = new_arg(line);
	if (new)
		ft_place_element_in_tern_tree(tmp, new, ft_strlen(new->arg));
	return (first);
}
