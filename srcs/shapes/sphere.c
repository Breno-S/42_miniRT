/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:40:48 by brensant          #+#    #+#             */
/*   Updated: 2026/05/14 17:15:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "vec_math.h"

void	set_matrix_sphere(t_obj *sphere)
{
	t_matrix	matrix;

	matrix = matrix_identity();
	matrix.m[0][0] = sphere->sphere.radius;
	matrix.m[1][1] = sphere->sphere.radius;
	matrix.m[2][2] = sphere->sphere.radius;
	matrix.m[0][3] = sphere->pos.x;
	matrix.m[1][3] = sphere->pos.y;
	matrix.m[2][3] = sphere->pos.z;
	sphere->matrix = matrix;
}
