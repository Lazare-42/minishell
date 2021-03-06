/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:09:39 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/20 15:58:53 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"

void	ft_put_command_errors(char *str)
{
	int i;

	i = 0;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
}

static int 	ft_return_alias_errors(int i, int underscore_nbr)
{
	if (i != 2 || underscore_nbr)
	{
		if (i != 2)
		{
			ft_putstr("alias : 2 arguments expected, you have ");
			ft_putnbr(i);
			ft_putstr(". \nIf this appears to be an error, you might want to ");
			ft_putstr("check if your new alias includes a pre-existing one.\n");
		}
		if (underscore_nbr)
		{
			ft_putstr("Underscores separate aliases in alias.txt ");
			ft_putstr("Please remove any underscore of the alias\n");
		}
		return (0);
	}
		ft_putstr("WTF");
	return (1);
}

int		ft_put_alias_errors(char **str)
{
	int i;
	int j;
	int	underscore_nbr;

	ft_putabs(str, '\n');
	i = 0;
	underscore_nbr = 0;
	j = -1;
	while (str && *str && str[i])
		i++;
	while (str[0][++j])
		if (str[0][j] == '_')
			underscore_nbr++;
	return (ft_return_alias_errors(i, underscore_nbr));
}
