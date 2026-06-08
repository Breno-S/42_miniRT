/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/06/08 13:14:54 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"
#include "utils.h"
#include "phong.h"

#include <float.h>
#include <math.h>

t_vec3	get_surface_color(t_hit *hit)
{
	int		u_idx;
	int		v_idx;
	float	pattern_size;

	if (hit->obj->phong_spec.b_type & CHK)
	{
		if (hit->obj->type == PLANE)
			pattern_size = 1.0;
		else
			pattern_size = 10.0;
		u_idx = floorf(hit->uv[0] * pattern_size);
		v_idx = floorf(hit->uv[1] * pattern_size);
		if ((u_idx + v_idx) % 2 == 0)
			return ((t_vec3){1, 1, 1, 1});
		return ((t_vec3){0, 0, 0, 1});
	}
	return (hit->obj->color_vec);
}

static t_hit	get_closest_collision(t_ray *ray, t_obj *list, int list_size)
{
	t_hit	hit;
	t_hit	closest;
	int		i;

	closest = hit_miss();
	i = 0;
	while (i < list_size)
	{
		hit = list[i].intersect(ray, &list[i]);
		if (hit.did_hit && hit.distance < closest.distance)
			closest = hit;
		i++;
	}
	if (closest.did_hit)
		set_uv_coords(&closest);
	return (closest);
}

static bool	check_shadow(t_rt *rt, t_vec3 hit_padded, t_light *light)
{
	t_vec3	to_light;
	t_ray	sec_ray;
	t_hit	sec_hit;

	to_light = vec3_sub(light->pos, rt->rc.closest_hit.point);
	sec_ray = ray_new(hit_padded, to_light);
	sec_hit = get_closest_collision(&sec_ray, rt->scene.obj,
			rt->scene.objs_num);
	light->to_light = vec3_length(to_light);
	return (!(sec_hit.did_hit && sec_hit.distance <= light->to_light));
}

static void	set_pixel_color(t_rt *rt)
{
	t_vec3	hit_padded;
	t_vec3	color_final;
	t_vec3	base_color;
	int		i;

	i = 0;
	color_final = (t_vec3){0};
	rt->rc.color = (t_color){.hex = BACKGROURD_COLOR};
	if (rt->rc.closest_hit.did_hit)
	{
		base_color = get_surface_color(&rt->rc.closest_hit);
		color_final = vec3_mult(base_color,
				vec3_scale(rt->scene.ambient.vec_color,
					rt->rc.closest_hit.obj->ka_final));
		hit_padded = vec3_add(rt->rc.closest_hit.point,
				vec3_scale(rt->rc.closest_hit.normal, 0.0001));
		while (i < rt->scene.lights_num)
		{
			if (check_shadow(rt, hit_padded, &rt->scene.lights[i]))
				color_final = vec3_add(get_color_light(rt->scene.lights[i],
							rt->rc.closest_hit, rt->rc.ray), color_final);
			i++;
		}
		rt->rc.color = color_from_vec(color_vec_clamp(color_final));
	}
}
// TODO: I DON'T KNOW
		// t_hit hit_obj = get_closest_collision(&(t_ray){hit_padded, reflected_ray}, rt->scene.obj, rt->scene.objs_num);
		// base_color = get_surface_color(&hit_obj);
		// rt->rc.color = color_from_vec(vec3_mult(base_color,
		// 		vec3_scale(rt->scene.ambient.vec_color,
		// 			hit_obj.obj->ka_final)));

t_color	ray_trace(t_rt *rt, int depth)
{
	t_vec3	reflected_ray;
	t_color	reflected_color;
	t_color	local_color;
	t_color	final_color;

	// Calcular a colisão mais próxima
	rt->rc.closest_hit = get_closest_collision(&rt->rc.ray,
			rt->scene.obj, rt->scene.objs_num);
	if (!rt->rc.closest_hit.did_hit)
	{
		rt->rc.color.hex = BACKGROURD_COLOR;
		return (rt->rc.color);
	}
	else
	{
		local_color.hex = BACKGROURD_COLOR;
	}
	// Se for refletivo e # de iterações < max
	if (rt->rc.closest_hit.obj->type == SPHERE && depth < 10)
	{
		reflected_ray = vec3_reflect(rt->rc.ray.dir, rt->rc.closest_hit.normal);
		reflected_color = ray_trace(rt, depth + 1);
		final_color.hex = BACKGROURD_COLOR;
	}
	else
		final_color = local_color;
	return (final_color);
}

void	rt_build_image(t_rt *rt)
{
	int		xy[2];

	xy[1] = 0;
	while (xy[1] < rt->mlx.height)
	{
		xy[0] = 0;
		while (xy[0] < rt->mlx.width)
		{
			// Calcular o pixel atual que será perpassado pelo raio.
			rt->rc.px = vec3_add(rt->rc.start, vec3_scale(rt->rc.dx, xy[0]));
			rt->rc.px = vec3_add(rt->rc.px, vec3_scale(rt->rc.dy, xy[1]));

			// Criar raio primário, que atravessa este pixel
			rt->rc.ray = ray_new(rt->rc.orig, (vec3_sub(rt->rc.px,
							rt->rc.orig)));
			ray_trace(rt, 0);
			// Calcular a colisão mais próxima
			// rt->rc.closest_hit = get_closest_collision(&rt->rc.ray,
			// 		rt->scene.obj, rt->scene.objs_num);
			if (rt->rc.closest_hit.obj->type == SPHERE)
				set_pixel_color(rt);
			else
				set_pixel_color(rt);
			pixel_put(&rt->mlx, xy[0], xy[1], rt->rc.color.hex);
			xy[0]++;
		}
		xy[1]++;
	}
}
