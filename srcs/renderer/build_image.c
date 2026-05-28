/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/05/28 14:33:47 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"
#include "utils.h"

#include <float.h>
#include <math.h>

static t_vec3	get_color_light(t_light light, t_hit hit, t_ray ray)
{
	t_vec3	reflected;
	t_vec3	light_dir;
	t_vec3	color_final;
	float	diffuse;
	float	specular;

	diffuse = 0;
	specular = 0;
	light_dir = vec3_normalize(vec3_sub(light.pos, hit.point));
	diffuse = fmax(vec3_dot(hit.normal, light_dir), 0.0)
		* hit.obj->phong_spec->kd;
	if (diffuse > 0)
	{
		reflected = vec3_normalize(vec3_reflect(vec3_negate(light_dir),
					hit.normal));
		specular = pow(fmax(vec3_dot(vec3_negate(ray.dir), reflected), 0.0),
				hit.obj->phong_spec->m) * hit.obj->phong_spec->ks;
	}
	color_final = vec3_mult(color_to_vec(hit.obj->color),
			vec3_scale(vec3_new(1, 1, 1), light.brightness * diffuse));
	color_final = vec3_add(color_final, vec3_scale(vec3_new(1, 1, 1),
				specular));
	return (color_final);
}

static t_color	ray_color(t_hit *hit, t_scene scene, t_ray *ray)
{
	t_vec3	color_final;
	t_vec3	color;

	if (hit->did_hit)
	{
		color = color_to_vec(hit->obj->color);
		color_final = vec3_mult(color_to_vec(hit->obj->color),
				vec3_scale(scene.ambient.vec_color, hit->obj->phong_spec->ka));
		color_final = vec3_add(get_color_light(scene.lights[0], hit[0], ray[0]),
				color_final);
		color.x = sqrt(color.x);
		color.y = sqrt(color.y);
		color.z = sqrt(color.z);
		return (color_from_vec(color_vec_clamp(color_final)));
	}
	return ((t_color){.hex = BACKGROURD_COLOR});
}

t_hit	get_closest_collision(t_ray *ray, t_obj *list, int list_size)
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
	return (closest);
}

static void	secondary_ray(t_rt *rt)
{
	t_vec3	hit_padded;
	t_vec3	to_light;
	t_ray	sec_ray;
	t_hit	sec_hit;

	if (rt->rc.closest_hit.did_hit)
	{
		hit_padded = vec3_add(rt->rc.closest_hit.point,
				vec3_scale(rt->rc.closest_hit.normal, 0.001));
		to_light = vec3_sub(rt->scene.lights[0].pos, rt->rc.closest_hit.point);
		sec_ray = ray_new(hit_padded, to_light);
		sec_hit = get_closest_collision(&sec_ray, rt->scene.obj,
				rt->scene.objs_num);
		if (!(sec_hit.did_hit && sec_hit.distance <= vec3_length(to_light)))
			rt->rc.color = ray_color(&rt->rc.closest_hit, rt->scene,
					&rt->rc.ray);
		else
			rt->rc.color = color_from_vec(vec3_mult(
						color_to_vec(rt->rc.closest_hit.obj->color),
						rt->scene.ambient.vec_color));
	}
	else
		rt->rc.color = (t_color){.hex = BACKGROURD_COLOR};
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
			rt->rc.px = vec3_add(rt->rc.start, vec3_scale(rt->rc.dx, xy[0]));
			rt->rc.px = vec3_add(rt->rc.px, vec3_scale(rt->rc.dy, xy[1]));
			rt->rc.ray = ray_new(rt->rc.orig, (vec3_sub(rt->rc.px,
							rt->rc.orig)));
			rt->rc.closest_hit = get_closest_collision(&rt->rc.ray,
					rt->scene.obj, rt->scene.objs_num);
			secondary_ray(rt);
			pixel_put(&rt->mlx, xy[0], xy[1], rt->rc.color.hex);
			xy[0]++;
		}
		xy[1]++;
	}
}
