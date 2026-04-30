/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/30 14:07:23 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "mlx.h"
#include "parser.h"
#include "ray_context.h"
#include "rt.h"
#include "vec_math.h"

#include <math.h>
#include <stdio.h>
#include "scene.h"

static int	finish_program(int rtn)
{
	ft_gc_end();
	return (rtn);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	ft_gc_init();
	rt = (t_rt){0};
	if (!rt_parse_args(&rt, argc, argv))
		return (finish_program(1));
	if (!rt.scene.lights)
		return (finish_program(1));
	if (!rt_mlx_setup(&rt, WIDTH, HEIGHT, "Ray Sniffer"))
		return (finish_program(1));
	rt_ray_context_setup(&rt);
	rt_render(&rt);
	if (rt.mlx.mlx_ptr)
		mlx_loop(rt.mlx.mlx_ptr);
	return (finish_program(0));
}
