/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 19:48:41 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"

#include <float.h>
#include <math.h>

static t_vec3	get_color_light(t_light light, t_hit hit, t_ray ray);
t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal);

static void	pixel_put(t_mlx_env *env, int x, int y, int color)
{
	char	*addr;
	int		i;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	addr = env->img_addr + (y * env->line_len + x * env->bpp / 8);
	i = env->bpp - 8;
	while (i >= 0)
	{
		if (env->endian != 0)
			*addr = (color >> i) & 0xFF;
		else
			*addr = (color >> (env->bpp - 8 - i)) & 0xFF;
		addr++;
		i -= 8;
	}
}

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	return (
		vec3_sub(
			incident,
			vec3_scale(
				normal,
				2.0 * vec3_dot(incident, normal)
			)
		)
	);
}

/**
 * TODO: add ambient light.
 */
static t_color	ray_color(t_hit *hit, t_scene scene, t_ray *ray)
{
	t_vec3	color_final;
	t_vec3	color;

	if (hit->did_hit)
	{
		color = color_to_vec(hit->obj->color);
		color_final = vec3_mult(color_to_vec(hit->obj->color),
			scene.ambient.vec_color);
		color_final = vec3_add(get_color_light(scene.lights[0], hit[0], ray[0]),
			color_final);
		color.x = sqrt(color.x);
		color.y = sqrt(color.y);
		color.z = sqrt(color.z);
		return (color_from_vec(color_vec_clamp(color_final)));
	}
	return ((t_color){.hex = BACKGROURD_COLOR});
}

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
	diffuse = fmax(vec3_dot(hit.normal, light_dir), 0.0);
	if (diffuse <= FLT_EPSILON)
		diffuse = 0;
	if (diffuse > 0)
	{
		reflected = vec3_normalize(vec3_reflect(vec3_negate(light_dir),
			hit.normal));
		specular = pow(fmax(vec3_dot(vec3_negate(vec3_normalize(ray.dir)),
			reflected), 0.0), SPECULAR_HIGHLIGHT) * SPECULAR_STRENGTH;
	}
	color_final = vec3_scale(color_to_vec(hit.obj->color),
		light.brightness * diffuse);
	color_final = vec3_add(color_final, vec3_scale(vec3_new(1, 1, 1),
		specular));
	return (color_final);
}

// TODO: STATIC
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

void	rt_build_image(t_rt *rt)
{
	int	xy[2];

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
			rt->rc.closest_hit = get_closest_collision(&rt->rc.ray, rt->scene.obj,
					rt->scene.objs_num);
			// Create secondary ray
			// if (rt->rc.closest_hit.did_hit)
			// {
			// 	t_ray	secondary_ray = ray_new(rt->rc.closest_hit.point, vec3_sub(rt->scene.lights[0].pos, rt->rc.closest_hit.point));
			// 	t_hit	secondary_hit = get_closest_collision(&secondary_ray, rt->scene.obj, rt->scene.objs_num);
			// 	rt->rc.closest_hit = get_closest_collision(&rt->rc.ray, rt->scene.obj,
			// 		rt->scene.objs_num);
			// 	rt->rc.color = ray_color(&secondary_hit, rt->scene, &secondary_ray);
			// }
			// else
				rt->rc.color = ray_color(&rt->rc.closest_hit, rt->scene, &rt->rc.ray);
			pixel_put(&rt->mlx, xy[0], xy[1], rt->rc.color.hex);
			xy[0]++;
		}
		xy[1]++;
	}
}
