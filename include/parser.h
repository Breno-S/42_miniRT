/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:54:17 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/08 16:05:18 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "shapes.h"
# include "libft.h"

typedef enum e_ent_type
{
	ambient	= 1,
	camera = 2,
	light = 4
}	t_ent_type;

typedef enum e_shpes_type
{
	tp_ambient	= 1,
	tp_camera = 2,
	tp_light = 3,
	tp_sphere = 4,
	tp_plane = 5,
	tp_cylinder = 6,
}	t_shpes_type;

int	parser(int ac, char **av);
int	error_msg(int err_type);

#endif
