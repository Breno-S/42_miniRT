/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/05/21 18:00:12 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "core.h"
#include "hit.h"
#include "mlx.h"
#include "ray.h"
#include "rt.h"
#include "ray_context.h"
#include "vec_math.h"
#include "shapes.h"

#include <math.h>
#include <float.h>

void	rt_render(t_rt *rt)
{
	t_ray_context	rc;

	rt_build_image(rt);
	mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
		rt->mlx.img_ptr, 0, 0);
}

static t_matrix	get_rotation_y_axis(t_camera *cam)
{
	t_matrix	mat;
	float		angle_y;
	float		cos_angle_y;
	float		sin_angle_y;

	angle_y = atan2f(cam->dir.x, cam->dir.z);
	cos_angle_y = cosf(angle_y);
	sin_angle_y = sinf(angle_y);
	mat = matrix_identity();
	mat.m[0][0] = cos_angle_y;
	mat.m[0][2] = sin_angle_y;
	mat.m[2][0] = -sin_angle_y;
	mat.m[2][2] = cos_angle_y;
	return (mat);
}

static t_matrix	get_rotation_x_axis(t_camera *cam)
{
	t_matrix	mat;
	float		angle_x;
	float		cos_angle_x;
	float		sin_angle_x;

	angle_x = atan2f(cam->dir.x, cam->dir.z);
	cos_angle_x = cosf(angle_x);
	sin_angle_x = sinf(angle_x);
	mat = matrix_identity();
	mat.m[1][1] = cos_angle_x;
	mat.m[1][2] = -sin_angle_x;
	mat.m[2][1] = sin_angle_x;
	mat.m[2][2] = cos_angle_x;
	return (mat);
}

static t_matrix	get_translation_matrix(t_camera *cam)
{
	t_matrix	mat;

	mat = matrix_identity();
	mat.m[0][3] = cam->pos.x;
	mat.m[1][3] = cam->pos.y;
	mat.m[2][3] = cam->pos.z;
	return (mat);
}

static void	setup_camera_matrix(t_camera *cam)
{
	t_matrix	mat_rotation_y;
	t_matrix	mat_rotation_x;
	t_matrix	mat_translation;
	t_matrix	final_transformation;

	mat_rotation_y = get_rotation_y_axis(cam);
	// Aplicar a rotação esquerda/direita antes de calcular a rotação cima/baixo

	mat_rotation_x = get_rotation_x_axis(cam);
	mat_translation = get_translation_matrix(cam);
	final_transformation = matrix_mult(matrix_mult());
}

void	rt_ray_context_setup(t_rt *rt)
{
	float	vp_width;
	float	vp_height;
	t_vec3	dummy_up;
	t_vec3	basis[3];
	t_vec3	xyz[3];

	rt->rc.orig = rt->scene.cam.pos;
	dummy_up = vec3_new(0, 1, 0);
	if (rt->scene.cam.dir.y == 1)
		dummy_up = vec3_new(0, 0, 1);
	if (rt->scene.cam.dir.y == -1)
		dummy_up = vec3_new(0, 0, -1);
	basis[0] = vec3_normalize(vec3_cross(rt->scene.cam.dir, dummy_up));
	basis[1] = vec3_normalize(vec3_cross(rt->scene.cam.dir, vec3_negate(basis[0])));
	basis[2] = rt->scene.cam.dir;
	vp_width = 2 * tanf(rt->scene.cam.fov * DEG2RAD / 2.0);
	vp_height = vp_width * ((float)rt->mlx.height / rt->mlx.width);
	xyz[0] = vec3_scale(basis[0], vp_width);
	xyz[1] = vec3_scale(basis[1], -vp_height);
	xyz[2] = vec3_scale(basis[2], FOCAL_DISTANCE);
	rt->rc.dx = vec3_scale(xyz[0], 1.0 / rt->mlx.width);
	rt->rc.dy = vec3_scale(xyz[1], 1.0 / rt->mlx.height);
	rt->rc.start = vec3_add(rt->scene.cam.pos, xyz[2]);
	rt->rc.start = vec3_add(rt->rc.start, vec3_negate(vec3_scale(xyz[0], 0.5)));
	rt->rc.start = vec3_add(rt->rc.start, vec3_negate(vec3_scale(xyz[1], 0.5)));
}
