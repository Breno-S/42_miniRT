/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:01:56 by brensant          #+#    #+#             */
/*   Updated: 2026/04/17 19:52:31 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>

static t_hit	get_hit_from_sphere(t_ray *ray, float a, float b, float c)
{
	t_hit	hit;
	float	discriminant;
	float	closest_hit_scalar;
	// float	farthest_hit_scalar;
	float	disc_sqrt;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_miss());
	disc_sqrt = sqrt(discriminant);
	closest_hit_scalar = (-b - disc_sqrt) / 2.0 * a;
	// farthest_hit_scalar = (-b + disc_sqrt) / 2.0 * a;
	hit.did_hit = true;
	hit.point = ray_at(ray, closest_hit_scalar);
	// hit.hit_in = ray_at(ray, closest_hit_scalar);
	// hit.hit_out = ray_at(ray, farthest_hit_scalar);
	hit.distance = vec3_length(vec3_sub(hit.point, ray->orig));
	return (hit);
}

/**
 * a = 1 -porque-> dot(ray->dir, ray->dir) = dot(1, 1)
 */
t_hit	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3	oc;
	float	b;
	float	c;

	oc = vec3_sub(sphere->center, ray->orig);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	return (get_hit_from_sphere(ray, 1, b, c));
}

t_hit	hit_miss(void)
{
	return ((t_hit){.did_hit = false});
}
