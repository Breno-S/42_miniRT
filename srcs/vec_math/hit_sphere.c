/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:12:44 by brensant          #+#    #+#             */
/*   Updated: 2026/04/19 18:13:12 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>

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
t_hit	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;
	t_vec3	oc;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(sphere->center, ray->orig);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (hit_miss());
	hit.did_hit = true;
	hit.sphere = sphere;
	set_hit(&hit, ray, b, discriminant);
	return (hit);
}
