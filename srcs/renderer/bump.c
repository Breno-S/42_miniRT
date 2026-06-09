/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:20:53 by brensant          #+#    #+#             */
/*   Updated: 2026/06/09 20:12:49 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	apply_bump_map(t_hit *hit)
{
	t_vec3  map_normal;
    t_vec3  new_normal;
    t_vec3  dummy_axis;
    t_vec3  tg;
    t_vec3  btg;

	//SO TA DANDO CERTO PARA PLANO
    if (fabsf(hit->normal.y) > 0.999f)
        dummy_axis = (t_vec3){1, 0, 0, 0};
    else
        dummy_axis = (t_vec3){0, 1, 0, 0};
    tg = vec3_normalize(vec3_cross(dummy_axis, hit->normal));
    btg = vec3_normalize(vec3_cross(tg, hit->normal));
    map_normal = get_map_value(hit, &hit->obj->phong_spec.normal);
	// Converter RGB [0.0, 1.0] para Vetor Direcional [-1.0, 1.0]
    map_normal = vec3_sub(vec3_scale(map_normal, 2), vec3_new(1,1,1));

    new_normal = vec3_scale(tg, map_normal.x);
    new_normal = vec3_add(new_normal, vec3_scale(btg, map_normal.y));
    new_normal = vec3_add(new_normal, vec3_scale(hit->normal, map_normal.z));
    hit->normal = vec3_normalize(new_normal);
}
