/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:13:13 by brensant          #+#    #+#             */
/*   Updated: 2026/04/23 02:26:03 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>
#include <float.h>

static bool	check_height(t_hit *hit, t_ray *ray, float t)
{
	if (t < FLT_EPSILON)
		return (false);
	hit->point = ray_at(ray, t);
	if (hit->point.y < hit->obj->pos.y - hit->obj->cylinder.height / 2
		|| hit->point.y > hit->obj->pos.y + hit->obj->cylinder.height / 2)
	{
		hit->distance = t;
		return (false);
	}
	return (true);
}

static void	set_hit(t_hit *hit, t_ray *ray, t_vec4 *coeff)
{
	float	closest_hit_scalar;
	float	farthest_hit_scalar;

	closest_hit_scalar = (-coeff->y - coeff->w) / (2.0 * coeff->x);
	farthest_hit_scalar = (-coeff->y + coeff->w) / 2.0 * coeff->x;
	// hit->hit_in = ray_at(ray, closest_hit_scalar);
	// hit->hit_out = ray_at(ray, farthest_hit_scalar);
	if (check_height(hit, ray, closest_hit_scalar)
		|| check_height(hit, ray, farthest_hit_scalar))
	{
		hit->did_hit = true;
		hit->normal = vec3_normalize((t_vec3){hit->point.x
				- hit->obj->pos.x, 0, hit->point.z - hit->obj->pos.z});
		if (vec3_dot(ray->dir, hit->normal) > 0)
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
 *
 * `a = 1` porque `a = dot(ray->dir, ray->dir)` e `|| ray->dir || = 1`
 */
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec4	coeff;

	oc = vec3_sub(ray->orig, cylinder->pos);
	coeff.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	coeff.y = 2.0 * (ray->dir.x * oc.x + ray->dir.z * oc.z);
	coeff.z = oc.x * oc.x + oc.z * oc.z
		- cylinder->cylinder.radius * cylinder->cylinder.radius;
	coeff.w = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (coeff.w < 0)
		return (hit_miss());
	coeff.w = sqrt(coeff.w);
	hit.obj = cylinder;
	set_hit(&hit, ray, &coeff);
	return (hit);
}
