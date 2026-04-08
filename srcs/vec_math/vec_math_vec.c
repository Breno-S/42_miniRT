/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:22 by brensant          #+#    #+#             */
/*   Updated: 2026/04/06 16:50:07 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

t_vec3	vec3_add(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3	vec3_sub(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){u.x - v.x, u.y - v.y, u.z - v.z});
}

float	vec3_dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){u.y * v.z - v.y * u.z, u.z * v.x - v.z * u.x,
		u.x * v.y - v.x * u.y});
}
