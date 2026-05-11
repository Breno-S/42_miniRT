/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:04:04 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 15:45:26 by rgomes-d         ###   ########.fr       */
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
	return ((t_vec4){.x = (float) color.r / 255.0f,
		.y = (float) color.g / 255.0f,
		.z = (float) color.b / 255.0f, .w = 1.0f});
}

t_color	color_from_vec(t_vec4 color)
{
	return ((t_color){
		.r = color.x * 255.0f,
		.g = color.y * 255.0f,
		.b = color.z * 255.0f,
		.a = 255.0f});
}
