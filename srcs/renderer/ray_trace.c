/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/06/12 14:44:46 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"
#include "utils.h"
#include "phong.h"

#include <float.h>
#include <math.h>

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
	{
		if (closest.obj->phong_spec.b_type & (B_CHK | B_NORMAL | B_COLOR))
		{
			set_uv_coords(&closest);
			if (closest.obj->phong_spec.b_type & (B_NORMAL | B_BUMP))
				handle_texture_maps(&closest);
		}
		closest.hit_padded = vec3_add(closest.point,
				vec3_scale(closest.normal, 0.0001));
	}
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

static t_color	set_pixel_color(t_rt *rt)
{
	t_vec3	color_final;
	int		i;

	i = 0;
	color_final = color_to_vec((t_color){BACKGROURD_COLOR});
	if (rt->rc.closest_hit.did_hit)
	{
		rt->rc.closest_hit.base_color
			= handle_surface_color(&rt->rc.closest_hit);
		color_final = vec3_mult(rt->rc.closest_hit.base_color,
				vec3_scale(rt->scene.ambient.vec_color,
					rt->rc.closest_hit.obj->ka_final));
		while (i < rt->scene.lights_num)
		{
			if (check_shadow(rt, rt->rc.closest_hit.hit_padded,
					&rt->scene.lights[i]))
				color_final = vec3_add(get_color_light(rt->scene.lights[i],
							rt->rc.closest_hit, rt->rc.ray), color_final);
			i++;
		}
	}
	return (color_from_vec(color_vec_clamp(color_final)));
}

t_color	ray_trace(t_rt *rt, int depth)
{
	t_color	reflected_color;
	t_color	local_color;
	t_color	final_color;
	float	local_kr;

	rt->rc.closest_hit = get_closest_collision(&rt->rc.ray,
			rt->scene.obj, rt->scene.objs_num);
	local_color.hex = BACKGROURD_COLOR;
	if (!rt->rc.closest_hit.did_hit)
		return (local_color);
	else
		local_color = set_pixel_color(rt);
	local_kr = rt->rc.closest_hit.obj->phong_spec.kr;
	if (local_kr > 0.0 && depth < MAX_DEPTH)
	{
		rt->rc.closest_hit.reflected = vec3_reflect(rt->rc.ray.dir,
				rt->rc.closest_hit.normal);
		rt->rc.ray = ray_new(rt->rc.closest_hit.hit_padded,
				rt->rc.closest_hit.reflected);
		reflected_color = ray_trace(rt, depth + 1);
		final_color = blend_color(local_color, reflected_color, local_kr);
	}
	else
		final_color = local_color;
	return (final_color);
}
