/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:13:32 by brensant          #+#    #+#             */
/*   Updated: 2026/04/29 18:14:03 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"

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
static t_color	ray_color(t_hit *hit, t_scene scene)
{
	float	intensity;

	if (hit->did_hit)
	{
		intensity = vec3_dot(hit->normal, vec3_normalize(vec3_sub(scene.lights[0].pos,
						hit->point)));
		if (intensity < 0)
			intensity = 0;
		return (color_from_vec(color_vec_clamp(vec3_scale(
						color_to_vec(hit->obj->color), intensity))));
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
	t_ray	ray;
	int		x;
	int		y;
	t_vec3	px_v;
	t_color	color;
	t_hit	closest_hit;

	if (!rt)
		return ;
	y = 0;
	while (y < rt->mlx.height)
	{
		x = 0;
		while (x < rt->mlx.width)
		{
			px_v = vec3_add(rt->rc.start, vec3_scale(rt->rc.dx, x));
			px_v = vec3_add(px_v, vec3_scale(rt->rc.dy, y));
			ray = ray_new(rt->rc.orig, vec3_normalize(vec3_sub(px_v, rt->rc.orig)));
			closest_hit = get_closest_collision(&ray, rt->scene.obj, rt->scene.objs_num);
			color = ray_color(&closest_hit, rt->scene);
			pixel_put(&rt->mlx, x, y, color.hex);
			x++;
		}
		y++;
	}
}
