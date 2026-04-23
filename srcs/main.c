/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/22 19:44:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "mlx.h"
#include "parser.h"
#include "renderer.h"
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
	t_env		*env;
	t_scene		scene;

	ft_gc_init();
	scene = parser(argc, argv);
	if (!scene.lights)
		return (finish_program(1));
	env = env_create(WIDTH, HEIGHT, "miniRT");
	renderer_render(env, scene);
	mlx_loop(env->mlx_ptr);
	env_destroy(env);
	return (finish_program(0));
}
