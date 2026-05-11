/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_unary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:22 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 16:45:31 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){.x = x, .y = y, .z = z, .w = 1});
}

float	vec3_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	return (vec3_scale(v, 1.0f / vec3_length(v)));
}

t_vec3	vec3_negate(t_vec3 v)
{
	return ((t_vec3){.x = -v.x, .y = -v.y, .z = -v.z, .w = 1});
}

t_vec3	vec3_scale(t_vec3 v, float scalar)
{
	return ((t_vec3){.x = scalar * v.x, .y = scalar * v.y, .z = scalar * v.z,
		.w = 1});
}
