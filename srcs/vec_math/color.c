/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:04:04 by brensant          #+#    #+#             */
/*   Updated: 2026/04/19 15:47:16 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vec_math.h"

#include <math.h>

t_vec4	color_vec_clamp(t_vec4 color_vec)
{
	float	max;

	max = fmaxf(color_vec.x, fmaxf(color_vec.y, color_vec.z));
	if (max > 1.0f)
		return (vec3_scale(color_vec, 1.0f / max));
	return (color_vec);
}

t_vec4	color_to_vec(t_color color)
{
	return ((t_vec4){.x = color.r / 255.0f, .y = color.g / 255.0f,
		.z = color.b / 255.0f, .w = 1.0f});
}

t_color	color_from_vec(t_vec4 color)
{
	return ((t_color){
		.r = color.x * 255.0f,
		.g = color.y * 255.0f,
		.b = color.z * 255.0f,
		.a = 255.0f});
}
