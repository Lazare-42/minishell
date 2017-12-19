/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/19 06:41:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>

static int	ft_compare_string_to_win(char *path, char *old_content, char *git, char *new_cont, char *line_right)
{
	struct	winsize window;
	int		arg_len;
	int		old_arg_len;

	arg_len = 0;
	arg_len = ft_strlen(path) + ft_strlen(git)
		+ ft_strlen(new_cont) + ft_strlen(line_right);
	old_arg_len = ft_strlen(path) + ft_strlen(git)
		+ ft_strlen(old_content) + ft_strlen(line_right);
	arg_len += (git) ? 9 : 5;
	old_arg_len += (git) ? 9 : 5;
	ioctl(1, TIOCGWINSZ, &window);
	if (arg_len == window.ws_col && old_arg_len > window.ws_col)
	{
		ft_putchar('\r');
		return (0);
	}
	else if (arg_len > window.ws_col)
		return (arg_len);
	else
		return (0);
}

static void ft_print_after_break(char *new_cont, int arg_len,
		char *old_content, char *line_right)
{
	int		window_size;
	int		path_len;
	int		new_cont_len;
	int		to_print_from;
	struct	winsize window;

	old_content = NULL;
	line_right = NULL;

	ioctl(1, TIOCGWINSZ, &window);
	window_size = window.ws_col;
	new_cont_len = ft_strlen(new_cont);
	path_len = (arg_len - new_cont_len);
	ft_putchar(' ');
	ft_putchar('\r');
	to_print_from = window_size - path_len;
	while ((int)ft_strlen(&(new_cont[to_print_from])) > window_size)
		to_print_from += window_size;
	ft_putstr(&(new_cont[to_print_from]));
}

static void ft_print_current_directory(char *path, char *git)
{
	if (path)
	{
		ft_putstr("\e[0;91m");
		ft_putchar('\r');
		ft_putchar('/');
		ft_putstr(path);
		if (git)
		{
			ft_putstr("\e[0m");
			ft_putstr("\e[0;90m");
			git ? ft_putstr("[git@]") : 0;
			git ? ft_putstr(git) : 0;
		}
	}
	ft_putstr("\\ ");
	ft_putstr("\e[0m");
}

void	ft_replace_content(char *old_content, char *new_cont,
		char *line_right)
{
	char	*path;
	char	*git;
	int		location_len;

	path = NULL;
	git = NULL;
	ft_get_location_info(&path, &git);
	if ((location_len = ft_compare_string_to_win(path, old_content,
					git, new_cont, line_right)))
	{
		ft_print_after_break(new_cont, location_len, old_content, line_right);
		return ;
	}
	ft_print_current_directory(path, git);
	if (old_content)
	{
		ft_putwhites(ft_strlen(old_content));
		ft_print_current_directory(path, git);
	}
	if (new_cont)
		ft_putstr(new_cont);
	if (line_right)
	{
		ft_putstr(line_right);
		ft_print_current_directory(path, git);
		ft_putstr(new_cont);
	}
}
