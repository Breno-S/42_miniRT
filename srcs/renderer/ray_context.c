/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_context.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:19:24 by brensant          #+#    #+#             */
/*   Updated: 2026/05/29 15:26:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>
#include <float.h>

static t_matrix	get_rotation_y_axis(t_camera *cam)
{
	t_matrix	mat;
	float		angle;
	float		cos_angle;
	float		sin_angle;

	angle = atan2f(cam->dir.x, cam->dir.z);
	cos_angle = cosf(angle);
	sin_angle = sinf(angle);
	mat = matrix_identity();
	mat.m[0][0] = cos_angle;
	mat.m[0][2] = sin_angle;
	mat.m[2][0] = -sin_angle;
	mat.m[2][2] = cos_angle;
	return (mat);
}

static t_matrix	get_rotation_x_axis(t_camera *cam)
{
	t_matrix	mat;
	float		angle;
	float		cos_angle;
	float		sin_angle;

	angle = atan2f(cam->dir.y, fabsf(cam->dir.z));
	if (cam->dir.z >= FLT_EPSILON)
		angle = -angle;
	cos_angle = cosf(angle);
	sin_angle = sinf(angle);
	mat = matrix_identity();
	mat.m[1][1] = cos_angle;
	mat.m[1][2] = -sin_angle;
	mat.m[2][1] = sin_angle;
	mat.m[2][2] = cos_angle;
	return (mat);
}

static t_matrix	get_cam_basis_matrix(t_camera *cam)
{
	t_matrix	mat_rotation_y;
	t_matrix	mat_rotation_x;
	t_matrix	camera_matrix;

	mat_rotation_y = get_rotation_y_axis(cam);
	mat_rotation_x = get_rotation_x_axis(cam);
	camera_matrix = matrix_mult(&mat_rotation_x, &mat_rotation_y);
	return (camera_matrix);
}

void	rt_ray_context_setup(t_rt *rt)
{
	t_matrix	cam_mat;
	float		vp_width;
	float		vp_height;
	t_vec3		basis[3];
	t_vec3		xyz[3];

	cam_mat = get_cam_basis_matrix(&rt->scene.cam);
	rt->rc.orig = rt->scene.cam.pos;
	basis[0] = vec3_transform((t_vec3){-1, 0, 0, 0}, &cam_mat);
	basis[1] = vec3_transform((t_vec3){0, 1, 0, 0}, &cam_mat);
	basis[2] = vec3_transform((t_vec3){0, 0, 1, 0}, &cam_mat);
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
