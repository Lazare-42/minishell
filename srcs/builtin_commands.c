/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:30:57 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 13:15:30 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_recognize_builtin_command(char *str)
{
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	int		i;

	i = 0;
	while (commands[i])
	{
		if (!(ft_strcmp(commands[i], str)))
				return (i);
		i++;
	}
	return (-1);
}
