/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:01:56 by brensant          #+#    #+#             */
/*   Updated: 2026/04/20 19:54:07 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>
#include <float.h>

static void	set_hit(t_hit *hit, t_ray *ray, float b, float discriminant)
{
	float	disc_sqrt;
	float	closest_hit_scalar;
	// float	farthest_hit_scalar;

	disc_sqrt = sqrt(discriminant);
	closest_hit_scalar = (-b - disc_sqrt) / 2.0;
	// farthest_hit_scalar = (-b + disc_sqrt) / 2.0;
	hit->point = ray_at(ray, closest_hit_scalar);
	// hit->hit_in = ray_at(ray, closest_hit_scalar);
	// hit->hit_out = ray_at(ray, farthest_hit_scalar);
	hit->distance = vec3_length(vec3_sub(hit->point, ray->orig));
}

/**
 * `a = 1` porque `a = dot(ray->dir, ray->dir)` e `|| ray->dir || = 1`
 */
t_hit	hit_sphere(t_ray *ray, t_obj *obj)
{
	t_hit	hit;
	t_vec3	oc;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(obj->pos, ray->orig);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (hit_miss());
	hit.did_hit = true;
	hit.obj = obj;
	set_hit(&hit, ray, b, discriminant);
	return (hit);
}

t_hit	hit_plane(t_ray *ray, t_obj *plane)
{
	t_hit	hit;
	t_vec3	orig_to_point;
	float	denominator;
	float	t;

	denominator = vec3_dot(plane->plane.normal, ray->dir);
	if (fabs(denominator) > FLT_EPSILON)
	{
		orig_to_point = vec3_sub(plane->pos, ray->orig);
		t = vec3_dot(orig_to_point, plane->plane.normal) / denominator;
		if (t >= FLT_EPSILON)
		{
			hit.did_hit = true;
			hit.point = ray_at(ray, t);
			hit.distance = t;
			hit.obj = plane;
			return (hit);
		}
	}
	return (hit_miss());
}


t_hit	hit_miss(void)
{
	return ((t_hit){.did_hit = false, .distance = INFINITY});
}
