/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:22 by brensant          #+#    #+#             */
/*   Updated: 2026/05/26 16:28:27 by brensant         ###   ########.fr       */
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

t_vec3	vec3_mult(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){.x = u.x * v.x, .y = u.y * v.y, .z = u.z * v.z, .w = 1});
}
