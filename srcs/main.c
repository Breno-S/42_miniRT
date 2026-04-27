/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/27 16:13:31 by brensant         ###   ########.fr       */
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

static int	close_window(t_env *env)
{
	env_destroy(env);
	return (0);
}

static int	handle_keypress(int keysym, t_env *env)
{
	if (keysym == 0xff1b)
		env_destroy(env);
	return (0);
}

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
	if (!env)
		return (finish_program(1));
	mlx_hook(env->win_ptr, 2, (1L << 0), handle_keypress, &env);
	mlx_hook(env->win_ptr, 17, 0, close_window, &env);
	renderer_render(env, scene);
	mlx_loop(env->mlx_ptr);
	env_destroy(env);
	return (finish_program(0));
}
