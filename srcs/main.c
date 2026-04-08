/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:39:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/08 14:09:09 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "vec_math.h"

#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include <math.h>

#define HEIGHT 1000
#define WIDTH 1000

typedef struct s_sphere
{
	t_vec3 center;
	double radius;
	t_vec3 color;
}	t_sphere;

int color_dot (t_vec3 color, double dot);
int color_dot_amb(t_vec3 color, double dot, double ambient);

int main(int argc, char **argv)
{
	t_env *env;

	ft_gc_init();

	env = env_create(WIDTH, HEIGHT);

	double ambient = 0.15;

	t_vec3	light = (t_vec3){0, 1, 1};

	t_sphere sphere = {.center = {-0.75, 0, 0}, .radius = 0.2, .color = {255,150,25}};
	t_sphere sphere2 = {.center = {0.75, 0, 0}, .radius = 0.2, .color = {150,25,255}};

	t_vec3	rec = (t_vec3){0.2, 0.3, 1};
	t_vec3	color3 = (t_vec3){255,255,255};

	printf("\nit's our miniRT. %f %d", sphere.radius, argc);
	fflush(stdout);

	t_vec3 act = (t_vec3){0};

	for (int y = 0; y < HEIGHT; y++)
	{
		act.y = 1.0 - ((2.0 * y) / HEIGHT);

		for (int x = 0; x < HEIGHT; x++)
		{
			t_vec3 normal;
			t_vec3 norm_light;
			double dot;
			t_vec3 d;
			double pd;

			act.x = ((2.0 * x) / WIDTH) - 1 ;

			// ponto - luz / || (ponto - luz)2 ||

			if ((powf(act.x - sphere.center.x, 2) + powf(act.y - sphere.center.y, 2)) <= powf(sphere.radius, 2))
			{
				d.y = act.y - sphere.center.y;
				d.x = act.x - sphere.center.x;
				pd = d.x * d.x + d.y * d.y;
				act.z = sqrt(sphere.radius * sphere.radius - pd);
				norm_light = vec3_normalize(vec3_sub(light, act));
				normal = vec3_scale((t_vec3){d.x, d.y, act.z}, 1.0 / sphere.radius);
				dot = vec3_dot(normal, norm_light);
				if (dot < 0)
					dot = 0;
				mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color_dot_amb(sphere.color, dot, ambient));
			}
			else if ((powf(act.x - sphere2.center.x, 2) + powf(act.y - sphere2.center.y, 2)) <= powf(sphere2.radius, 2))
			{
				d.y = act.y - sphere2.center.y;
				d.x = act.x - sphere2.center.x;
				pd = d.x * d.x + d.y * d.y;
				act.z = sqrt(sphere2.radius * sphere2.radius - pd);
				norm_light = vec3_normalize(vec3_sub(light, act));
				normal = vec3_scale((t_vec3){d.x, d.y, act.z}, 1.0 / sphere2.radius);
				dot = vec3_dot(normal, norm_light);
				if (dot < 0)
					dot = 0;
				mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color_dot_amb(sphere2.color, dot, ambient));
			}
			else if ((act.x - rec.x) > -0.2 && (act.x - rec.x) < 0.2 && (act.y - rec.x)  > -0.2 && (act.y - rec.x)  < 0.2)
			{
				d.y = act.y - sphere2.center.y;
				d.x = act.x - sphere2.center.x;
    			mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, 0x00FF00);
			}
			else
				mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color_dot_amb(color3, 0, 0));
		}
	}
	mlx_loop(env->mlx_ptr);
	env_destroy(env);
	ft_gc_end();
    return (0);
}


int color_dot_union(t_vec3 color, double dot)
{
	t_vec3 new_color;

	new_color = vec3_scale(color, dot);
	if (new_color.x > 255)
		new_color.x = 255;
	if (new_color.y > 255)
		new_color.y = 255;
	if (new_color.z > 255)
		new_color.z = 255;
	return (color_to_rgb(new_color));
}

int color_dot_amb(t_vec3 color, double dot, double ambient)
{
	t_vec3 new_color;

	new_color = vec3_scale(color, (dot + ambient));
	while (new_color.x > 255 || new_color.z > 255 || new_color.y > 255)
	{
		if (new_color.x > 255)
		{
			new_color.y += ((int)new_color.x % 255) /2;
			new_color.z += ((int)new_color.x % 255) /2;
			new_color.x = 255;
		}
		if (new_color.y > 255)
		{
			new_color.z += ((int)new_color.y % 255) /2;
			new_color.x += ((int)new_color.y % 255) /2;
			new_color.y = 255;
		}
		if (new_color.z > 255)
		{
			new_color.y += ((int)new_color.z % 255) /2;
			new_color.x += ((int)new_color.z % 255) /2;
			new_color.z = 255;
		}
	}
	return (color_to_rgb(new_color));
}
