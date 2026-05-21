/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 01:33:38 by brensant          #+#    #+#             */
/*   Updated: 2026/05/21 16:43:31 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

#include <math.h>

t_vec3	vec3_transform(t_vec3 v, void *mat)
{
	float	x;
	float	y;
	float	z;
	float	w;
	float	**m;

	m = (float **)((t_matrix *)mat)->m;
	x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + 1 * m[0][3];
	y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + 1 * m[1][3];
	z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + 1 * m[2][3];
	w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + 1 * m[3][3];
	return ((t_vec3){.x = x, .y = y, .z = z, .w = w});
}

float	vec3_distance(t_vec3 u, t_vec3 v)
{
	return (sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y)
			+ (v.z - u.z) * (v.z - u.z)));
}

t_matrix	matrix_identity(void)
{
	return (t_matrix){.m[0][0] = 1, .m[1][1] = 1, .m[2][2] = 1, .m[3][3] = 1};
}

t_matrix	matrix_mult(t_matrix *left, t_matrix *right)
{
	t_matrix	result;
	int 		i;
	int 		j;
	int 		k;

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
