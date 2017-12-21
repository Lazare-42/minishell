/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:26:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 03:07:52 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>

static int	ft_compare_string_to_win(char *path, char *git, t_arg *line_info)
{
	struct	winsize window;
	int		arg_len;


	arg_len = 0;
	arg_len = ft_strlen(path) + ft_strlen(git)
		+ ft_strlen(line_info->arg) + ft_strlen(line_info->line_right);
	//	old_arg_len = ft_strlen(path) + ft_strlen(git)
	//		+ ft_strlen(erase) + ft_strlen(line_right);
	arg_len += (git) ? 9 : 5;
	//	old_arg_len += (git) ? 9 : 5;
	ioctl(1, TIOCGWINSZ, &window);
	if (arg_len == window.ws_col)
		//	&& old_arg_len > window.ws_col)
	{
		ft_putchar('\r');
		return (0);
	}
	else if (arg_len > window.ws_col)
		return (arg_len);
	else
		return (0);
}

static void ft_print_after_break(t_arg *line_info, int arg_len)
{
	int		window_size;
	int		path_len;
	int		new_cont_len;
	int		to_print_from;
	struct	winsize window;


	ioctl(1, TIOCGWINSZ, &window);
	window_size = window.ws_col;
	new_cont_len = ft_strlen(line_info->arg) + ft_strlen(line_info->line_right);
	path_len = (arg_len - new_cont_len);
	ft_putstr(" ");
	ft_putchar('\r');
	to_print_from = window_size - path_len;
	while ((int)ft_strlen(&(line_info->arg[to_print_from])) > window_size)
		to_print_from += window_size;
	ft_putstr(&(line_info->arg[to_print_from]));
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

void	ft_replace_content(t_arg *line_info)
{
	char	*path;
	char	*git;
	int		location_len;

	path = NULL;
	git = NULL;
	ft_get_location_info(&path, &git);
	if (line_info && (location_len = ft_compare_string_to_win(path, git, line_info)))
	{
		ft_print_after_break(line_info, location_len);
		return ;
	}
	ft_print_current_directory(path, git);
	if (line_info)
	{
		(line_info->old_line) ? ft_putwhites(ft_strlen(line_info->old_line)) : 0;
		(line_info->old_line) ? ft_print_current_directory(path, git) : 0;
		(line_info->arg) ? ft_putstr(line_info->arg) : 0;
		(line_info->line_right) ? ft_putstr(line_info->line_right) : 0;
		(line_info->line_right) ? ft_print_current_directory(path, git) : 0;
		(line_info->line_right) ? ft_putstr(line_info->arg): 0;
	}
}
