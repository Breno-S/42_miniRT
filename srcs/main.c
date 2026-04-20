/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/20 19:43:35 by brensant         ###   ########.fr       */
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
	t_rt_list	*rt_list;
	t_scene		scene;
	t_obj		*obj;

	obj = (t_obj *)ft_gc_calloc(1, 8, GC_DATA);
	scene.ambient.i_rate = 0;
	ft_gc_init();
	if (parser(argc, argv))
		return (finish_program(1));
	rt_list = ft_to_gc_list(
			ft_gc_call_root("ent")->lst->head->content)->content;
	obj[0].sphere.radius = rt_list->next->next->next->obj.sphere.radius;
	env = env_create(WIDTH, HEIGHT, "miniRT");
	renderer_render(env);
	mlx_loop(env->mlx_ptr);
	env_destroy(env);
	return (finish_program(0));
}
