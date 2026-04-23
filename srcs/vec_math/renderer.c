/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/04/23 16:06:21 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "hit.h"
#include "mlx.h"
#include "ray.h"
#include "renderer.h"
#include "vec_math.h"
#include "shapes.h"

#include <math.h>

/****************************** FOR DEBUG ONLY ********************************/

t_obj		g_objs[5] = {
{SPHERE, {4.5, 0, 4, 1}, (t_color){.hex = 0xFF0000}, .sphere.radius = 2,},
{SPHERE, {-4.5, 0, 4, 1}, (t_color){.hex = 0xFF0000}, .sphere.radius = 2,},
// {SPHERE, {0, 4.5, 4, 1}, (t_color){.hex = 0x0000FF}, .sphere.radius = 2,},
// {SPHERE, {0, -4.5, 4, 1}, (t_color){.hex = 0xFFFF00}, .sphere.radius = 2,},
{CYLINDER, {0, 0, 4, 1}, (t_color){.hex = 0xFF0000}, .cylinder.axis = {0, 1, 0, 0}, .cylinder.radius = 2, .cylinder.height = 8},
{PLANE, {0, 0, 10, 1}, (t_color){.hex = 0xA1A1A1}, .plane.normal = {-1, 0, 1, 1}},
{PLANE, {0, 0, 10, 1}, (t_color){.hex = 0xA1A1A1}, .plane.normal = {1, 0, 1, 1}}
};

t_camera	g_camera = {CAMERA, {0, 0, -10, 1}, {0, 0, 1, 1}, 70};

t_light		g_light = {LIGHT, {0, 0, 0, 1}, 1.0, (t_color){.hex = 0xFFFFFF}};

// t_ambient g_ambient = {0.0, (t_color){.hex = 0xFFFFFF}};

/******************************************************************************/

static void	pixel_put(t_env *env, int x, int y, int color)
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
static t_color	ray_color(t_hit *hit)
{
	t_vec3	normal;
	float	intensity;

	if (hit->did_hit)
	{
		intensity = vec3_dot(hit->normal, vec3_normalize(vec3_sub(g_light.pos,
						hit->point)));
		if (intensity < 0)
			intensity = 0;
		return (color_from_vec(color_vec_clamp(vec3_scale(
						color_to_vec(hit->obj->color), intensity))));
	}
	return ((t_color){.hex = BACKGROURD_COLOR});
}

/**
 * TODO: call generic `hit_obj()` function in t_obj struct.
 */
t_hit	get_closest_collision(t_ray *ray, t_obj *list, int list_size)
{
	t_hit	hit;
	t_hit	closest;
	int		i;

	closest = hit_miss();
	i = 0;
	while (i < list_size)
	{
		if (list[i].type == SPHERE)
			hit = hit_sphere(ray, &list[i]);
		else if (list[i].type == CYLINDER)
			hit = hit_cylinder(ray, &list[i]);
		else if (list[i].type == PLANE)
			hit = hit_plane(ray, &list[i]);
		if (hit.did_hit && hit.distance < closest.distance)
			closest = hit;
		i++;
	}
	return (closest);
}

static void	build_image(t_env *env, t_ray_context rc)
{
	t_ray	ray;
	int		x;
	int		y;
	t_vec3	pixel_v;
	t_color	color;
	t_hit	closest_hit;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_v = vec3_add(rc.vp_start, vec3_scale(rc.vp_dx, x));
			pixel_v = vec3_add(pixel_v, vec3_scale(rc.vp_dy, y));
			ray = ray_new(rc.orig, vec3_normalize(vec3_sub(pixel_v, rc.orig)));
			closest_hit = get_closest_collision(&ray, g_objs, 5);
			color = ray_color(&closest_hit);
			pixel_put(env, x, y, color.hex);
			x++;
		}
		y++;
	}
}

t_ray_context	get_ray_context(t_env *env, t_camera *camera)
{
	t_ray_context	rc;
	float			vp_width;
	float			vp_height;

	rc.orig = camera->pos;
	vp_width = 2 * tanf(camera->fov * DEG2RAD / 2.0);
	vp_height = vp_width * ((float)env->height / env->width);
	rc.vp_w_vec = vec3_new(vp_width, 0, 0);
	rc.vp_h_vec = vec3_new(0, -vp_height, 0);
	rc.vp_fd_vec = vec3_new(0, 0, FOCAL_DISTANCE);
	rc.vp_dx = vec3_scale(rc.vp_w_vec, 1.0 / env->width);
	rc.vp_dy = vec3_scale(rc.vp_h_vec, 1.0 / env->height);
	rc.vp_start = vec3_add(camera->pos, rc.vp_fd_vec);
	rc.vp_start = vec3_add(rc.vp_start, vec3_negate(vec3_scale(rc.vp_w_vec,
					0.5)));
	rc.vp_start = vec3_add(rc.vp_start, vec3_negate(vec3_scale(rc.vp_h_vec,
					0.5)));
	return (rc);
}

void	renderer_render(t_env *env)
{
	t_ray_context	rc;

	rc = get_ray_context(env, &g_camera);
	build_image(env, rc);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}
