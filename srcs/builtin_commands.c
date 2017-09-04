/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:30:57 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/04 16:59:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_recognize_command(char *str)
{
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	int		i;

	i = 0;
	while (commands[i])
	{
		if (!(ft_strcmp(*commands, str)))
				return (i);
		ft_putchar('\n');
		i++;
	}
	return (-1);
}
