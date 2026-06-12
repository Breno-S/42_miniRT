/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 19:32:11 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/10 22:24:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

#include <math.h>
#include <float.h>

static float	get_visible_scalar(t_hit *hit, t_ray *ray, float t0, float t1)
{
	float	half_height;
	t_vec3	p;
	float	proj;

	half_height = hit->obj->cone.height / 2.0;
	if (t0 > FLT_EPSILON)
	{
		p = ray_at(ray, t0);
		proj = vec3_dot(vec3_sub(p, hit->obj->pos), hit->obj->cone.axis);
		if (proj >= -half_height && proj <= 0)
			return (t0);
	}
	if (t1 > FLT_EPSILON)
	{
		p = ray_at(ray, t1);
		proj = vec3_dot(vec3_sub(p, hit->obj->pos), hit->obj->cone.axis);
		if (proj >= -half_height && proj <= 0)
			return (t1);
	}
	return (-1);
}

static void	set_normal(t_hit *hit, t_obj *cone)
{
	t_vec3	v;
	t_vec3	radial;
	float	h;
	float	k;
	float	k2;

	v = vec3_sub(hit->point, cone->pos);
	h = vec3_dot(v, cone->cone.axis);
	radial = vec3_sub(v, vec3_scale(cone->cone.axis, h));
	k = (cone->cone.radius * 2.0f) / cone->cone.height;
	k2 = k * k;
	hit->normal = vec3_normalize(vec3_sub(radial, vec3_scale(cone->cone.axis,
					k2 * h)));
}

static void	set_hit(t_hit *hit, t_ray *ray, t_vec4 *coeff)
{
	float	closest_hit_scalar;
	float	farthest_hit_scalar;
	float	t;

	closest_hit_scalar = (-coeff->y - coeff->w) / (2.0 * coeff->x);
	farthest_hit_scalar = (-coeff->y + coeff->w) / (2.0 * coeff->x);
	t = get_visible_scalar(hit, ray, closest_hit_scalar, farthest_hit_scalar);
	if (t >= FLT_EPSILON)
	{
		hit->did_hit = true;
		hit->distance = t;
		hit->point = ray_at(ray, t);
		set_normal(hit, hit->obj);
		if (vec3_dot(ray->dir, hit->normal) > FLT_EPSILON)
			hit->normal = vec3_negate(hit->normal);
	}
	else
		*hit = hit_miss();
}

/**
 * `coeff.x = a;
 * `coeff.y = b;
 * `coeff.z = c;
 * `coeff.w = sqrt(discriminant);
 */
t_hit	hit_cone(t_ray *ray, t_obj *cone)
{
	t_hit	hit;
	t_vec4	coeff;
	t_vec3	oc[2];
	t_vec3	d_perp;
	t_vec3	proj;

	oc[0] = vec3_sub(ray->orig, cone->pos);
	proj.x = vec3_dot(ray->dir, cone->cone.axis);
	proj.y = vec3_dot(oc[0], cone->cone.axis);
	proj.z = (cone->cone.radius / cone->cone.height * 2)
		* (cone->cone.radius / cone->cone.height * 2);
	d_perp = vec3_sub(ray->dir, vec3_scale(cone->cone.axis, proj.x));
	oc[1] = vec3_sub(oc[0], vec3_scale(cone->cone.axis, proj.y));
	coeff.x = vec3_dot(d_perp, d_perp) - proj.z * (proj.x * proj.x);
	coeff.y = 2.0 * (vec3_dot(d_perp, oc[1]) - proj.z * (proj.x * proj.y));
	coeff.z = vec3_dot(oc[1], oc[1]) - proj.z * (proj.y * proj.y);
	coeff.w = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (coeff.w < 0)
		return (hit_miss());
	coeff.w = sqrt(coeff.w);
	if (coeff.w < FLT_EPSILON)
		return (hit_miss());
	hit.obj = cone;
	set_hit(&hit, ray, &coeff);
	return (hit);
}
