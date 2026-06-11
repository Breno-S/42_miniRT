/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/10 16:51:40 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "mlx.h"
#include "parser.h"
#include "ray_context.h"
#include "rt.h"
#include "utils.h"
#include "vec_math.h"

#include <math.h>
#include <stdio.h>
#include "scene.h"

static int	finish_program(t_rt rt, int rtn)
{
	int	i;

	i = 0;
	if (rt.scene.lights)
	{
		while (i < rt.scene.objs_num)
		{
			if (rt.scene.obj[i].phong_spec.b_type & B_NORMAL)
				mlx_destroy_image(rt.mlx.mlx_ptr,
					rt.scene.obj[i].phong_spec.normal.img);
			if (rt.scene.obj[i].phong_spec.b_type & B_COLOR)
				mlx_destroy_image(rt.mlx.mlx_ptr,
					rt.scene.obj[i].phong_spec.color.img);
			i++;
		}
	}
	ft_gc_end();
	return (rtn);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	ft_gc_init();
	rt = (t_rt){0};
	if (!rt_parse_args(&rt, argc, argv))
	{
		ft_gc_end();
		return (1);
	}
	if (!rt_mlx_setup(&rt, WIDTH, HEIGHT, "Ray Sniffer"))
		return (finish_program(rt, 1));
	create_textures(&rt);
	rt_render(&rt);
	if (rt.mlx.mlx_ptr)
		mlx_loop(rt.mlx.mlx_ptr);
	return (finish_program(rt, 0));
}
