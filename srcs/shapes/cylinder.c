/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 15:04:39 by brensant          #+#    #+#             */
/*   Updated: 2026/05/14 17:10:38 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "vec_math.h"

void	set_matrix_cylinder(t_obj *cylinder, t_vec3 *pos, t_vec3 *axis, float *height,
	float *radius)
{
	t_matrix	matrix;

	matrix = matrix_identity();
	if (fabsf(vec3_dot(*axis, (t_vec3){0, 1, 0})) == 1)
	{

	}
	// Radius
	matrix.m[0][0] = *radius;
	matrix.m[2][2] = *radius;
	matrix.m[0][3] = pos->x;
	matrix.m[1][3] = pos->y;
	matrix.m[2][3] = pos->z;
}
