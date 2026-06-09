/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:20:53 by brensant          #+#    #+#             */
/*   Updated: 2026/06/09 18:56:39 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_bump_map(t_hit *hit)
{
	t_vec3	normal;
	t_vec3	dummy_axis;
	t_vec3	tg;
	t_vec3	btg;

	if (fabsf(hit->normal.y) == 1)
		dummy_axis = (t_vec3){1, 0, 0, 0};
	else
		dummy_axis = (t_vec3){0, 1, 0, 0};
	tg = vec3_normalize(vec3_cross(dummy_axis, hit->normal));
	btg = vec3_cross(tg, hit->normal);
	normal = vec3_normalize(get_map_value(hit, &hit->obj->phong_spec.normal));
	// hit->normal = vec3_add(vec3_scale(normal), hit->normal);
	hit->normal = vec3_add(hit->normal, vec3_scale(tg, vec3_dot(normal, tg)));
	hit->normal = vec3_add(hit->normal, vec3_scale(btg, vec3_dot(normal, btg)));
	hit->normal = vec3_add(hit->normal, vec3_scale(tg, normal.y));
}
