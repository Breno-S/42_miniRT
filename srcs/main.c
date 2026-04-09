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
	t_env		*env;

	ft_gc_init();
	env = env_create(WIDTH, HEIGHT, "miniRT");
	renderer_render(env);
	// double ambient = 0.15;

	// t_vec3	light = (t_vec3){0, -1, 1};

	// t_sphere sphere = {.center = {-0.5, 0, 0}, .radius = 0.25, .color.hex = 0x40ed5f};
	// t_sphere sphere2 = {.center = {0.5, 0, 0}, .radius = 0.25, .color.hex = 0xFF0000};
	// printf("\nit's our miniRT. %f %d", sphere.radius, argc);
	// fflush(stdout);

	// t_vec3 act = (t_vec3){0};

	// for (int y = 0; y < HEIGHT; y++)
	// {
	// 	act.y = 1.0 - ((2.0 * y) / HEIGHT);

	// 	for (int x = 0; x < HEIGHT; x++)
	// 	{
	// 		t_vec3 normal;
	// 		t_vec3 norm_light;
	// 		double dot;
	// 		t_vec3 d;
	// 		double pd;

	// 		act.x = ((2.0 * x) / WIDTH) - 1 ;

	// 		// ponto - luz / || (ponto - luz)2 ||

	// 		if ((powf(act.x - sphere.center.x, 2) + powf(act.y - sphere.center.y, 2)) <= powf(sphere.radius, 2))
	// 		{
	// 			d.y = act.y - sphere.center.y;
	// 			d.x = act.x - sphere.center.x;
	// 			pd = d.x * d.x + d.y * d.y;
	// 			act.z = sqrt(sphere.radius * sphere.radius - pd);
	// 			norm_light = vec3_normalize(vec3_sub(light, act));
	// 			normal = vec3_scale((t_vec3){d.x, d.y, act.z}, 1.0 / sphere.radius);
	// 			dot = vec3_dot(normal, norm_light);
	// 			if (dot < 0)
	// 				dot = 0;
	// 			mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color_apply_shading(sphere.color, dot, ambient).hex);
	// 		}
	// 		else if ((powf(act.x - sphere2.center.x, 2) + powf(act.y - sphere2.center.y, 2)) <= powf(sphere2.radius, 2))
	// 		{
	// 			d.y = act.y - sphere2.center.y;
	// 			d.x = act.x - sphere2.center.x;
	// 			pd = d.x * d.x + d.y * d.y;
	// 			act.z = sqrt(sphere2.radius * sphere2.radius - pd);
	// 			norm_light = vec3_normalize(vec3_sub(light, act));
	// 			normal = vec3_scale((t_vec3){d.x, d.y, act.z}, 1.0 / sphere2.radius);
	// 			dot = vec3_dot(normal, norm_light);
	// 			if (dot < 0)
	// 				dot = 0;
	// 			mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color_apply_shading(sphere2.color, dot, ambient).hex);
	// 		}
	// 	}
	// }
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
