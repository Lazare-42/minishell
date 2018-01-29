/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:32:05 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 11:42:55 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_standby(void)
{
	ft_putchar('\r');
	ft_putstr("dquote> ");
}

char	*ft_del_one(char *command_line, int write_from)
{
	if (*command_line && &command_line[write_from])
	{
		(command_line)[ft_strlen(command_line) - 1] = ' ';
		ft_standby();
		ft_putstr(&command_line[write_from]);
		(command_line)[ft_strlen(command_line) - 1] = '\0';
		ft_standby();
		ft_putstr(&command_line[write_from]);
	}
	return (command_line);
}

char	*ft_join_print(char *command_line, int buf, int write_from)
{
	if (!(command_line = ft_strjoinfree_str_char(&command_line, buf)))
		return (NULL);
	ft_standby();
	ft_putstr(&command_line[write_from]);
	return (command_line);
}

void	ft_complete_command(int quote_type, char **command_line, t_arg **first)
{
	int		comma_presence;
	int		ret;
	long	buf;
	int		write_from;

	ft_putstr("dquote> ");
	ret = 1;
	write_from = ft_strlen(*command_line) - 1;
	while (ret == 1 && command_line)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (buf == 127 && command_line[0])
			*command_line = ft_del_one(*command_line, write_from);
		else if (buf == '\n')
			break ;
		// i deleted buf != KEY_UP LEFT DOWN RIGHT
		else if (buf != 127 
				)
			*command_line = ft_join_print(*command_line, buf, write_from);
	}
	comma_presence = ft_check_commas(*command_line);
	ft_putchar('\n');
	(comma_presence != quote_type) ?
		ft_recognize_processes(*command_line, first)
		: ft_complete_command(quote_type, command_line, first);
}
