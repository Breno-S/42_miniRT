/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:59:12 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/12 13:09:15 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"

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

	color_final = (t_vec3){0};
	if (diff > 0)
		color_final = vec3_scale(vec3_mult(hit.base_color, color_light),
				diff);
	if (spec > 0)
		color_final = vec3_add(color_final, vec3_scale(color_light, spec));
	return (color_final);
}

t_color	blend_color(t_color color1, t_color color2, float kr)
{
	t_vec3	v_color1;
	t_vec3	v_color2;
	t_vec3	final_color;

	v_color1 = color_to_vec(color1);
	v_color2 = color_to_vec(color2);
	final_color = vec3_add(vec3_scale(v_color1, (1 - kr)),
			vec3_scale(v_color2, (kr)));
	return (color_from_vec(final_color));
}
