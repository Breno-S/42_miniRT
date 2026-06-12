/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:13:13 by brensant          #+#    #+#             */
/*   Updated: 2026/05/27 21:13:45 by brensant         ###   ########.fr       */
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

	half_height = hit->obj->cylinder.height / 2.0;
	if (t0 > FLT_EPSILON)
	{
		p = ray_at(ray, t0);
		proj = vec3_dot(vec3_sub(p, hit->obj->pos), hit->obj->cylinder.axis);
		if (proj >= -half_height && proj <= half_height)
			return (t0);
	}
	if (t1 > FLT_EPSILON)
	{
		p = ray_at(ray, t1);
		proj = vec3_dot(vec3_sub(p, hit->obj->pos), hit->obj->cylinder.axis);
		if (proj >= -half_height && proj <= half_height)
			return (t1);
	}
	return (-1);
}

static void	set_hit(t_hit *hit, t_ray *ray, t_vec4 *coeff)
{
	float	closest_hit_scalar;
	float	farthest_hit_scalar;
	float	t;
	t_vec3	cp;
	t_vec3	proj;

	closest_hit_scalar = (-coeff->y - coeff->w) / (2.0 * coeff->x);
	farthest_hit_scalar = (-coeff->y + coeff->w) / (2.0 * coeff->x);
	t = get_visible_scalar(hit, ray, closest_hit_scalar, farthest_hit_scalar);
	if (t >= FLT_EPSILON)
	{
		hit->did_hit = true;
		hit->distance = t;
		hit->point = ray_at(ray, t);
		cp = vec3_sub(hit->point, hit->obj->pos);
		proj = vec3_scale(hit->obj->cylinder.axis,
				vec3_dot(cp, hit->obj->cylinder.axis));
		hit->normal = vec3_normalize(vec3_sub(cp, proj));
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
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec4	coeff;
	t_vec3	d_perp;
	t_vec3	oc_perp;

	oc = vec3_sub(ray->orig, cylinder->pos);
	d_perp = vec3_sub(ray->dir, vec3_scale(cylinder->cylinder.axis,
				vec3_dot(ray->dir, cylinder->cylinder.axis)));
	oc_perp = vec3_sub(oc, vec3_scale(cylinder->cylinder.axis,
				vec3_dot(oc, cylinder->cylinder.axis)));
	coeff.x = vec3_dot(d_perp, d_perp);
	coeff.y = 2.0 * vec3_dot(d_perp, oc_perp);
	coeff.z = vec3_dot(oc_perp, oc_perp)
		- cylinder->cylinder.radius * cylinder->cylinder.radius;
	coeff.w = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (coeff.w < 0)
		return (hit_miss());
	coeff.w = sqrt(coeff.w);
	if (coeff.w < FLT_EPSILON)
		return (hit_miss());
	hit.obj = cylinder;
	set_hit(&hit, ray, &coeff);
	return (hit);
}
