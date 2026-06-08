/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:59:12 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/08 12:57:05 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "rt.h"
#include "utils.h"
#include "phong.h"

#include <float.h>
#include <math.h>

t_vec3	get_color_light(t_light light, t_hit hit, t_ray ray)
{
	t_vec3	reflected;
	t_vec3	light_dir;
	float	attenuation;
	float	diff;
	float	spec;

	diff = 0;
	spec = 0;
	light_dir = vec3_normalize(vec3_sub(light.pos, hit.point));
	attenuation = (D1 + D2 * light.to_light + D3
			* (light.to_light * light.to_light));
	if (attenuation == 0)
		attenuation = 0.000001;
	attenuation = (light.brightness / attenuation);
	diff = fmax(vec3_dot(hit.normal, light_dir), 0.0) * hit.obj->phong_spec.kd
		* attenuation;
	if (diff > 0)
	{
		reflected = vec3_normalize(vec3_reflect(vec3_negate(light_dir),
					hit.normal));
		spec = pow(fmax(vec3_dot(vec3_negate(ray.dir), reflected), 0.0),
				hit.obj->phong_spec.m) * hit.obj->phong_spec.ks * attenuation;
	}
	return (get_new_color(diff, spec, light.vec_color, hit));
}

t_vec3	get_new_color(float diff, float spec, t_vec3 color_light, t_hit hit)
{
	t_vec3	color_final;
	t_vec3	base_color;

	color_final = (t_vec3){0};
	base_color = get_surface_color(&hit);
	if (diff > 0)
		color_final = vec3_scale(vec3_mult(hit.obj->color_vec, color_light),
				diff);
	if (spec > 0)
		color_final = vec3_add(color_final, vec3_scale(color_light, spec));
	return (color_final);
}
