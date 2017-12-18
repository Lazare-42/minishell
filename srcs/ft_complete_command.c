/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:32:05 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 19:35:38 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_standby()
{
			ft_putchar('\r');
			ft_putstr("dquote> ");
}

void	ft_complete_command(int quote_type, char **command_line)
{
	char    *new_line;
	int		comma_presence;
	int		ret;
	long	buf;

	if (!(new_line = ft_strnew(0)))
		return ;
	ft_putstr("dquote> ");
	ret = 1;
	while (ret == 1)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (buf == 127 && new_line[0])
		{
			(new_line)[ft_strlen(new_line) - 1] = ' ';
			ft_standby();
			ft_putstr(new_line);
			(new_line)[ft_strlen(new_line) - 1] = '\0';
			ft_standby();
			ft_putstr(new_line);
		}
		else if (buf == '\n')
			break ;
		else if (buf != 127 && buf != KEY_UP && buf
				!= KEY_DOWN && buf != KEY_LEFT && buf != KEY_RIGHT)
		{
			new_line = ft_strjoinfree_str_char(&new_line, buf);
			ft_standby();
			ft_putstr(new_line);
		}
	}
	*command_line = ft_strjoinfree(command_line, &new_line, 'B');
	comma_presence = ft_check_commas(*command_line);
	ft_putchar('\n');
	(comma_presence != quote_type) ? ft_recognize_processes(*command_line) :
		ft_complete_command(quote_type, command_line);
}
