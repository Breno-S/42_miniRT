/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/04/19 15:18:34 by brensant         ###   ########.fr       */
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

t_sphere sphere = {{0, 0, 4, 1}, 1, (t_color){.hex = 0xFF0000}};

// t_plane plane = {{5, 0, 0, 1}, {-1, 0, 0, 1}, (t_color){.hex = 0xffffff}};
// t_plane plane2 = {{0, -1, 0, 1}, {0, 1, 0, 1}, (t_color){.hex = 0xFFff10}};
// t_plane plane3 = {{-5, 0, 0, 1}, {-1, 0, 0, 1}, (t_color){.hex = 0xffffff}};

t_camera camera = {{0, 0, 0, 1}, {0, 0, 1, 1}, 70};

t_light light = {{0,5,2,1}, 1.0, (t_color){.hex = 0xFFFFFF}};

t_ambient ambient = {0.0, (t_color){.hex = 0xFFFFFF}};

float	hit_plane(t_plane plane, t_ray ray, float *t);
static t_color	ray_to_plane(float t, t_ray ray, t_plane *plane);
static t_color	ray_to_sphere(float t, t_ray ray, t_sphere *sphere);

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

static t_color	ray_color(t_sphere *sphere, t_ray *ray)
{
	t_hit	hit;
	t_vec3	normal;
	t_vec3	light_dir;
	float	intensity;

	hit = hit_sphere(ray, sphere);
	if (hit.did_hit)
	{
		normal = vec3_normalize(vec3_sub(hit.point, sphere->center));
		light_dir = vec3_normalize(vec3_new(1, 1, -1));
		intensity = vec3_dot(normal, light_dir);
		if (intensity < 0)
			intensity = 0;
		return (color_from_vec(vec3_scale(color_to_vec(sphere->color),
					intensity)));
	}
	return ((t_color){.hex = 0x202020});
}

static void	build_image(t_env *env, t_ray_context rc)
{
	t_ray	ray;
	int		x;
	int		y;
	t_vec3	curr_pixel_vec;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			curr_pixel_vec = vec3_add(rc.vp_start, vec3_scale(rc.vp_dx, x));
			curr_pixel_vec = vec3_add(curr_pixel_vec, vec3_scale(rc.vp_dy, y));
			ray = ray_new(camera.pos, vec3_normalize(vec3_sub(curr_pixel_vec,
				camera.pos)));
			// Get closest collision
			// Compute color at intersection point
			color = ray_color(&sphere, &ray);
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

	rc = get_ray_context(env, &camera);
	build_image(env, rc);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}
