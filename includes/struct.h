/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:14:52 by lazrossi          #+#    #+#             */
/*   Updated: 2018/01/04 14:23:14 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_arg
{
	char			*arg;
	char			*line_right;
	char			*old_line;
	struct s_arg	*next;
	struct s_arg	*previous;
}					t_arg;
#endif
