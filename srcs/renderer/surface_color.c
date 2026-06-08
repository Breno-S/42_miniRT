/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:27:13 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/08 19:26:02 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"
#include "utils.h"

#include <float.h>
#include <math.h>

t_vec3	get_surface_color(t_hit *hit)
{
	int	x;
	int	y;
	t_color	pixel_value;

	x = roundf(hit->uv[0] * hit->obj->phong_spec.color.width);
	y = roundf(hit->uv[1] * hit->obj->phong_spec.color.height);
	pixel_value = (t_color){.hex = hit->obj->phong_spec.color.img_addr[y
		* hit->obj->phong_spec.color.size_line + x]};
	return (color_to_vec(pixel_value));
}

t_vec3	handle_surface_color(t_hit *hit)
{
	if (hit->obj->phong_spec.b_type & CHK)
		return (get_surface_chk(hit));
	else if (hit->obj->phong_spec.b_type & NORMAL_COLOR)
		return (get_surface_normal(hit));
	else if (hit->obj->phong_spec.b_type & COLOR)
		return (get_surface_color(hit));
	return (hit->obj->color_vec);
}

t_vec3	get_surface_chk(t_hit *hit)
{
	int		u_idx;
	int		v_idx;
	float	pattern_size;

	if (hit->obj->type == PLANE)
		pattern_size = 1.0;
	else
		pattern_size = 10.0;
	u_idx = floorf(hit->uv[0] * pattern_size);
	v_idx = floorf(hit->uv[1] * pattern_size);
	if ((u_idx + v_idx) % 2 == 0)
		return ((t_vec3){1, 1, 1, 1});
	return ((t_vec3){0, 0, 0, 1});
}

t_vec3	get_surface_normal(t_hit *hit)
{
	return (vec3_scale(vec3_add(hit->normal, vec3_new(1, 1, 1)), 0.5));
}
