/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:20:53 by brensant          #+#    #+#             */
/*   Updated: 2026/06/12 14:43:30 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <float.h>
#include <math.h>
#include <mlx.h>

void	handle_texture_maps(t_hit *hit)
{
	t_vec3	dummy_axis;
	t_vec3	tg;
	t_vec3	btg;
	float	dot_nt;

	if (hit->obj->type == PLANE)
	{
		dummy_axis = (t_vec3){0, 1, 0, 0};
		if (fabsf(hit->normal.y) > 0.999f)
			dummy_axis = (t_vec3){1, 0, 0, 0};
		tg = vec3_normalize(vec3_cross(dummy_axis, hit->normal));
	}
	else
	{
		tg = vec3_normalize((t_vec3){-hit->normal.z, 0, hit->normal.x, 0});
		if (fabsf(hit->normal.y) > 0.999f)
			tg = (t_vec3){1, 0, 0, 0};
	}
	dot_nt = vec3_dot(hit->normal, tg);
	tg = vec3_normalize(vec3_sub(tg, vec3_scale(hit->normal, dot_nt)));
	btg = vec3_normalize(vec3_cross(tg, hit->normal));
	apply_bump_map(hit, tg, btg);
	apply_normal_map(hit, tg, btg);
}

void	apply_normal_map(t_hit *hit, t_vec3 tg, t_vec3 btg)
{
	t_vec3	new_normal;
	t_vec3	map_normal;

	if (hit->obj->phong_spec.b_type & B_NORMAL)
	{
		map_normal = get_map_value(hit, &hit->obj->phong_spec.normal);
		map_normal = vec3_sub(vec3_scale(map_normal, 2), vec3_new(1, 1, 1));
		new_normal = vec3_scale(tg, map_normal.x);
		new_normal = vec3_add(new_normal, vec3_scale(btg, map_normal.y));
		new_normal = vec3_add(new_normal,
				vec3_scale(hit->normal, map_normal.z));
		hit->normal = vec3_normalize(new_normal);
	}
}

void	apply_bump_map(t_hit *hit, t_vec3 tg, t_vec3 btg)
{
	float	h_center;
	float	h_u;
	float	h_v;
	float	du;
	float	dv;

	if (hit->obj->phong_spec.b_type & B_BUMP)
	{
		h_center = get_map_value(hit, &hit->obj->phong_spec.bump).x;
		hit->uv[0] += FLT_EPSILON;
		h_u = get_map_value(hit, &hit->obj->phong_spec.bump).x;
		hit->uv[0] -= FLT_EPSILON;
		hit->uv[1] += FLT_EPSILON;
		h_v = get_map_value(hit, &hit->obj->phong_spec.bump).x;
		hit->uv[1] -= FLT_EPSILON;
		du = (h_u - h_center) * BUMP_STRENGHT;
		dv = (h_v - h_center) * BUMP_STRENGHT;
		hit->normal = vec3_sub(hit->normal, vec3_scale(tg, du));
		hit->normal = vec3_sub(hit->normal, vec3_scale(btg, dv));
		hit->normal = vec3_normalize(hit->normal);
	}
}
