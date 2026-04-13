/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:04:04 by brensant          #+#    #+#             */
/*   Updated: 2026/04/08 17:23:47 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vec_math.h"

#include <math.h>

t_vec4	color_vec_clamp(t_vec4 color)
{
	float	max;

	max = fmaxf(color.x, fmaxf(color.y, color.z));
	if (max > 255)
		return (vec3_scale(color, 255.0 / max));
	return (color);
}

t_vec4	color_to_vec(t_color color)
{
	return ((t_vec4){.x = color.r, .y = color.g, .z = color.b, .w = 255});
}

t_color	color_from_vec(t_vec4 color)
{
	return ((t_color){
		.r = color.x,
		.g = color.y,
		.b = color.z});
}
