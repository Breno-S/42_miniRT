/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/19 15:30:51 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
// #include "core.h"

// static int	finish_program(int rtn);

// int	main(int ac, char **av)
// {
// 	t_rt_list	*ent;

// 	ft_gc_init();
// 	if (parser(ac, av))
// 		return (finish_program(1));
// 	ent = ft_to_gc_list(ft_gc_call_root("ent")->lst->head->content)->content;
// 	return (finish_program(0));
// }

// static int	finish_program(int rtn)
// {
// 	ft_gc_end();
// 	return (rtn);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:39:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/10 02:19:04 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "libft.h"
#include "mlx.h"
#include "renderer.h"
#include "vec_math.h"

#include <math.h>
#include <stdio.h>

t_color	color_apply_shading(t_color color, double dot, double ambient);

int main(int argc, char **argv)
{
	t_env	*env;

	ft_gc_init();
	env = env_create(WIDTH, HEIGHT, "miniRT");
	renderer_render(env);
	mlx_loop(env->mlx_ptr);
	env_destroy(env);
	ft_gc_end();
	return (0);
}

t_color	color_apply_shading(t_color color, double dot, double ambient)
{
	t_vec4	new_color;

	new_color = color_to_vec(color);
	new_color = vec3_scale(new_color, (dot + ambient));
	new_color = color_vec_clamp(new_color);
	return (color_from_vec(new_color));
}
