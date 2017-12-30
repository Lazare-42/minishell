/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/30 22:00:31 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <term.h>

static int	set_non_canonical_input(void)
{
	struct termios termios_cpy;

	if (tcgetattr(0, &termios_cpy) != 0)
		return (0);
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return (0);
	return (1);
}

int		main(void)
{
	extern char **environ;
	t_arg	*first;

	first = NULL;
	first = ft_store_args(first, NULL);
	if (!(set_non_canonical_input()))
		return (put_fatal_error("could not set non-canonical input"));
	if (!(environ = ft_tabdup(environ, ft_tabsize(environ))))
		return (put_fatal_error("malloc error while copying tab"));
	ft_print_current_directory();
	return (ft_file_to_string(first));
}
