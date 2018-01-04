/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 01:12:30 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 11:52:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/ioctl.h>

int	window_info(int info_request)
{
	struct winsize window;

	if (ioctl(1, TIOCGWINSZ, &window) == -1)
		put_error("ioctl error");
	if (info_request == 1)
		return (window.ws_col);
	if (info_request == 2)
		return (window.ws_row);
	return (0);
}
