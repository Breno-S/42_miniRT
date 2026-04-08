/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:22 by brensant          #+#    #+#             */
/*   Updated: 2026/04/07 15:16:01 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

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
	return ((t_vec3){-v.x, -v.y, -v.z});
}

t_vec3	vec3_scale(t_vec3 v, float scalar)
{
	return ((t_vec3){scalar * v.x, scalar * v.y, scalar * v.z});
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
	return ((t_vec3){x, y, z, w});
}
