/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:06:47 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/05 15:17:31 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;

int	main()
{
	int i;
	char *path;
	char c[] = "user";

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5))
		i++;*
	path = environ[i];

	while (strcmp(<F7>


