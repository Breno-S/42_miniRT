/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:22 by brensant          #+#    #+#             */
/*   Updated: 2026/04/09 14:08:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

t_vec3	vec3_add(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){.x = u.x + v.x, .y = u.y + v.y, .z = u.z + v.z, .w = 1});
}

t_vec3	vec3_sub(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){.x = u.x - v.x, .y = u.y - v.y, .z = u.z - v.z, .w = 1});
}

float	vec3_dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){.x = u.y * v.z - v.y * u.z, .y = u.z * v.x - v.z * u.x,
		.z = u.x * v.y - v.x * u.y, .w = 1});
}

t_vec3	vec3_transform(t_vec3 v, t_matrix m)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = v.x * m.r0[0] + v.y * m.r0[1] + v.z * m.r0[2] + 1 * m.r0[3];
	y = v.x * m.r1[0] + v.y * m.r1[1] + v.z * m.r1[2] + 1 * m.r1[3];
	z = v.x * m.r2[0] + v.y * m.r2[1] + v.z * m.r2[2] + 1 * m.r2[3];
	w = v.x * m.r3[0] + v.y * m.r3[1] + v.z * m.r3[2] + 1 * m.r3[3];
	return ((t_vec3){.x = x, .y = y, .z = z, .w = w});
}
