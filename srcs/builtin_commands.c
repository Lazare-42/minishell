/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:43:35 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 16:55:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *g_commands[9] = {"echo", "cd", "setenv", "unsetenv", "env",
	"exit", "chdir", "alias"};

int		ft_recognize_builtin_command(char *str)
{
	int		i;

	i = 0;
	while (g_commands[i])
	{
		if (ft_strcmp((char*)g_commands[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}
