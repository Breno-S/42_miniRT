/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:36:14 by brensant          #+#    #+#             */
/*   Updated: 2026/05/14 17:33:31 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "vec_math.h"

void	set_matrix_plane(t_obj *plane)
{
	t_vec3		rotation_axis;
	t_matrix	matrix;

	matrix = matrix_identity();
	matrix.m[0][3] = plane->pos.x;
	matrix.m[1][3] = plane->pos.y;
	matrix.m[2][3] = plane->pos.z;
	if (fabsf(vec3_dot(plane->plane.normal, (t_vec3){0, 1, 0})) == 1)
	{
		plane->matrix = matrix;
		return ;
	}
	rotation_axis = vec3_cross(plane->plane.normal, (t_vec3){0, 1, 0});
}
