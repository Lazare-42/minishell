/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:47:06 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/20 13:00:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

void	ft_delete(char **alias_name, char **alias_value)
{
	if (*alias_name)
		ft_memdel((void**)alias_name);
	if (*alias_value)
		ft_memdel((void**)alias_value);
}

void	ft_add_alias(char **alias_name, char **alias_value, char **new_values)
{
	if (!(*alias_name = ft_strjoinfree_str_char(alias_name, '_')))
		return ;
	if (!(*alias_name = ft_strjoinfree(alias_name, &(new_values[0]), 'L')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_name = ft_strjoinfree_str_char(alias_name, '\n')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree_str_char(alias_value, ',')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree(alias_value, &(new_values[1]), 'L')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree_str_char(alias_value, '\n')))
		ft_delete(alias_name, alias_value);
}

void	ft_creat_alias(char **alias_name, char **alias_value, char **new_values)
{
	if (!(*alias_name = ft_strjoin(new_values[0], "\n")))
		return ;
	if (!(*alias_value = ft_strjoin(new_values[1], "\n")))
		ft_delete(alias_name, alias_value);
}

void	ft_new_alias(char **new_values)
{
	int		fd;
	char	*alias_name;
	char	*alias_value;

	fd = -1;
	alias_value = NULL;
	alias_name = NULL;
	if (!(ft_put_alias_errors(new_values)))
		return ;
	if (!(fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt",
					O_RDWR | O_CREAT, 0777)))
		return ;
	get_next_line(fd, &alias_name, '\n');
	get_next_line(fd, &alias_value, '\n');
	close(fd);
	if (alias_name && alias_value)
		ft_add_alias(&alias_name, &alias_value, new_values);
	else
		ft_creat_alias(&alias_name, &alias_value, new_values);
	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt", O_RDWR);
	write(fd, alias_name, ft_strlen(alias_name));
	write(fd, alias_value, ft_strlen(alias_value));
	ft_delete(&alias_name, &alias_value);
	close(fd);
}
