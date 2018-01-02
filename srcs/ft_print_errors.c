/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:09:39 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/30 21:35:27 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	ft_put_command_errors(char *str)
{
	int i;

	i = 0;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
}

void	put_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
	ft_print_current_directory();
}

int		put_fatal_error(char *str)
{
	ft_putstr_fd("\nQuitting minishell process for the following reason : ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar('.');
	ft_putchar('\n');
	return (0);
}
