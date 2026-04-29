/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/29 12:53:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "mlx.h"
#include "parser.h"
#include "renderer.h"
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
	if (!rt_mlx_env_setup(&rt, WIDTH, HEIGHT, "Ray Sniffer"))
		return (finish_program(1));
	renderer_render(&rt.mlx_env, rt.scene);
	mlx_loop(rt.mlx_env.mlx_ptr);
	rt_mlx_env_destroy(&rt);
	return (finish_program(0));
}
