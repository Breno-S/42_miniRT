/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_coords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:10:28 by brensant          #+#    #+#             */
/*   Updated: 2026/06/02 15:55:26 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>
#include <float.h>

static void	set_uv_coords_co(t_hit *hit, t_obj *cone)
{
	t_vec3	vp;
	t_vec3	dummy_x_axis;
	t_vec3	dummy_z_axis;
	t_vec3	out_vec;
	float	hit_height;

	vp = vec3_sub(cone->pos, hit->point);
	hit_height = vec3_dot(vp, cone->cone.axis);
	hit->uv[1] = hit_height / cone->cone.height;
	if (fabsf(cone->cone.axis.y) == 1)
		dummy_x_axis = vec3_normalize(
				vec3_cross((t_vec3){1, 0, 0}, cone->cone.axis));
	else
		dummy_x_axis = vec3_normalize(
				vec3_cross((t_vec3){0, 1, 0}, cone->cone.axis));
	dummy_z_axis = vec3_cross(cone->cone.axis, dummy_x_axis);
	out_vec = vec3_sub(hit->point, vec3_sub(cone->pos,
				vec3_scale(cone->cone.axis, hit_height)));
	hit->uv[0] = 0.5 + (atan2f(vec3_dot(out_vec, dummy_z_axis),
				vec3_dot(out_vec, dummy_x_axis)) / (2 * PI));
}

static void	set_uv_coords_cy(t_hit *hit, t_obj *cylinder)
{
	t_vec3	cp;
	t_vec3	dummy_x_axis;
	t_vec3	dummy_z_axis;
	t_vec3	out_vec;
	float	hit_height;

	cp = vec3_sub(hit->point, cylinder->pos);
	hit_height = vec3_dot(cp, cylinder->cylinder.axis);
	hit->uv[1] = hit_height / cylinder->cylinder.height;
	if (fabsf(cylinder->cylinder.axis.y) == 1)
		dummy_x_axis = vec3_normalize(
				vec3_cross((t_vec3){1, 0, 0}, cylinder->cylinder.axis));
	else
		dummy_x_axis = vec3_normalize(
				vec3_cross((t_vec3){0, 1, 0}, cylinder->cylinder.axis));
	dummy_z_axis = vec3_cross(cylinder->cylinder.axis, dummy_x_axis);
	out_vec = vec3_sub(cp, vec3_scale(cylinder->cylinder.axis, hit_height));
	hit->uv[0] = 0.5 + (atan2f(vec3_dot(out_vec, dummy_z_axis),
				vec3_dot(out_vec, dummy_x_axis)) / (2 * PI));
}

static void	set_uv_coords_sp(t_hit *hit, t_obj *sphere)
{
	hit->uv[0] = 0.5 + (atan2f(hit->normal.z, hit->normal.x) / (2 * PI));
	hit->uv[1] = 0.5 - (asinf(hit->normal.y) / PI);
}

static void	set_uv_coords_pl(t_hit *hit, t_obj *plane)
{
	t_vec3	dummy_axis;
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	diff;

	if (fabsf(plane->plane.normal.y) == 1)
		dummy_axis = (t_vec3){1, 0, 0};
	else
		dummy_axis = (t_vec3){0, 1, 0};
	u_axis = vec3_normalize(vec3_cross(dummy_axis, plane->plane.normal));
	v_axis = vec3_cross(plane->plane.normal, u_axis);
	diff = vec3_sub(hit->point, plane->pos);
	hit->uv[0] = vec3_dot(diff, u_axis);
	hit->uv[1] = vec3_dot(diff, v_axis);
}

void	set_uv_coords(t_hit *hit)
{
	if (!hit->did_hit)
		return ;
	if (hit->obj->type == PLANE)
		set_uv_coords_pl(hit, hit->obj);
	if (hit->obj->type == SPHERE)
		set_uv_coords_sp(hit, hit->obj);
	if (hit->obj->type == CYLINDER)
		set_uv_coords_cy(hit, hit->obj);
	if (hit->obj->type == CONE)
		set_uv_coords_co(hit, hit->obj);
}
