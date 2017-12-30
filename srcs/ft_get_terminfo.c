/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_terminfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:37:33 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/30 19:52:49 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <term.h>
#include <stdlib.h>

int	get_terminal_description(void)
{
	char	*term_type;

	term_type = NULL;
	if (!(term_type = getenv("TERM")))
	{
		ft_putstr("Impossible to locate terminal environement variable,");
		ft_putstr("switching by default to vt100\n");
		term_type = "vt100";
	}
	if ((tgetent(NULL, term_type)) != 1)
	{
		ft_putstr("Impossible to interrogate the terminal description\n");
		return (0);
	}
	return (1);
}
