/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/06/12 16:56:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "phong.h"
#include "utils.h"

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
