/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 01:33:38 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 16:45:31 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

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

float	vec3_distance(t_vec3 u, t_vec3 v)
{
	return (sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y)
			+ (v.z - u.z) * (v.z - u.z)));
}
