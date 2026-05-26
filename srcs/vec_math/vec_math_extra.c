/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 01:33:38 by brensant          #+#    #+#             */
/*   Updated: 2026/05/26 17:32:38 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

float	vec3_distance(t_vec3 u, t_vec3 v)
{
	return (sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y)
			+ (v.z - u.z) * (v.z - u.z)));
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 mirror_normal)
{
	return (vec3_sub(v, vec3_scale(mirror_normal,
				2.0 * vec3_dot(v, mirror_normal))));
}

t_vec3	vec3_transform(t_vec3 v, t_matrix *m)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = v.x * m->m[0][0] + v.y * m->m[0][1] + v.z * m->m[0][2]
		+ v.w * m->m[0][3];
	y = v.x * m->m[1][0] + v.y * m->m[1][1] + v.z * m->m[1][2]
		+ v.w * m->m[1][3];
	z = v.x * m->m[2][0] + v.y * m->m[2][1] + v.z * m->m[2][2]
		+ v.w * m->m[2][3];
	w = v.x * m->m[3][0] + v.y * m->m[3][1] + v.z * m->m[3][2]
		+ v.w * m->m[3][3];
	return ((t_vec3){.x = x, .y = y, .z = z, .w = w});
}

t_matrix	matrix_identity(void)
{
	return ((t_matrix){.m[0][0] = 1, .m[1][1] = 1, .m[2][2] = 1, .m[3][3] = 1});
}

t_matrix	matrix_mult(t_matrix *left, t_matrix *right)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += left->m[i][k] * right->m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}
