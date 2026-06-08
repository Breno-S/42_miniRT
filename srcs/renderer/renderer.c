/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/06/08 15:11:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "hit.h"
#include "mlx.h"
#include "ray.h"
#include "rt.h"
#include "phong.h"
#include "ray_context.h"
#include "vec_math.h"
#include "shapes.h"
#include "utils.h"

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

void	rt_build_image(t_rt *rt)
{
	int	x;
	int	y;

	y = 0;
	while (y < rt->mlx.height)
	{
		x = 0;
		while (x < rt->mlx.width)
		{
			rt->rc.px = vec3_add(rt->rc.start, vec3_scale(rt->rc.dx, x));
			rt->rc.px = vec3_add(rt->rc.px, vec3_scale(rt->rc.dy, y));
			rt->rc.ray = ray_new(rt->rc.orig, (vec3_sub(rt->rc.px,
							rt->rc.orig)));
			rt->rc.color = ray_trace(rt, 0);
			pixel_put(&rt->mlx, x, y, rt->rc.color.hex);
			x++;
		}
		y++;
	}
}

void	rt_render(t_rt *rt)
{
	rt_ray_context_setup(rt);
	rt_build_image(rt);
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img_ptr, 0, 0);
}
