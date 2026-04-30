/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/04/30 20:23:24 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"

#include <float.h>
#include <math.h>

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

/**
 * TODO: add ambient light.
 */
static t_color	ray_color(t_hit *hit, t_scene scene, t_ray *ray)
{
	float	i_final;
	float	diffuse;
	float	specular;
	float	specular_strenth;
	t_vec3	reflected;
	t_vec3	ligth_dir;

	ligth_dir = vec3_normalize(vec3_sub(scene.lights[0].pos, hit->point));
	if (hit->did_hit)
	{
		diffuse = vec3_dot(hit->normal, ligth_dir);
		if (diffuse < FLT_EPSILON)
			diffuse = 0;
		reflected = vec3_sub(vec3_scale(hit->normal, vec3_dot(vec3_negate(ligth_dir), hit->normal) * 2), ligth_dir);
		specular = pow(fmax(vec3_dot(reflected, vec3_negate(ray->dir)), 0.0), 255);
		if (specular < FLT_EPSILON)
			specular = 0;
		i_final = scene.ambient.i_rate + diffuse + specular;
		return (color_from_vec(color_vec_clamp(vec3_scale(
						color_to_vec(hit->obj->color), i_final))));
	}
	return ((t_color){.hex = BACKGROURD_COLOR});
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
			rt->rc.ray = ray_new(rt->rc.orig, vec3_normalize(vec3_sub(rt->rc.px,
							rt->rc.orig)));
			rt->rc.closest_hit = get_closest_collision(&rt->rc.ray, rt->scene.obj,
					rt->scene.objs_num);
			rt->rc.color = ray_color(&rt->rc.closest_hit, rt->scene, &rt->rc.ray);
			pixel_put(&rt->mlx, xy[0], xy[1], rt->rc.color.hex);
			xy[0]++;
		}
		xy[1]++;
	}
}
