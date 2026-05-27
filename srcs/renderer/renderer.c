/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/05/27 14:35:15 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "hit.h"
#include "mlx.h"
#include "ray.h"
#include "rt.h"
#include "ray_context.h"
#include "vec_math.h"
#include "shapes.h"

#include <math.h>
#include <float.h>
#include <stdio.h>

// void	print_matrix(t_matrix m)
// {
// 	for (size_t i = 0; i < 4; i++)
// 	{
// 		for (size_t j = 0; j < 4; j++)
// 		{
// 			printf("%f ", m.m[i][j]);
// 		}
// 			printf("\n");
// 	}
// 	printf("\n");
// }

void	rt_render(t_rt *rt)
{
	rt_ray_context_setup(rt);
	rt_build_image(rt);
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img_ptr, 0, 0);
}
