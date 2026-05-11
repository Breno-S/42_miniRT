/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:12:44 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 15:45:26 by rgomes-d         ###   ########.fr       */
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

	disc_sqrt = sqrt(discriminant);
	closest_hit_scalar = (-b - disc_sqrt) / 2.0;
	if (closest_hit_scalar >= FLT_EPSILON)
	{
		hit->point = ray_at(ray, closest_hit_scalar);
		hit->distance = closest_hit_scalar;
		hit->normal = vec3_normalize(vec3_sub(hit->point, hit->obj->pos));
	}
	else
		*hit = hit_miss();
}

/**
 * `a = 1` porque `a = dot(ray->dir, ray->dir)` e `|| ray->dir || = 1`
 */
t_hit	hit_sphere(t_ray *ray, t_obj *sphere)
{
	t_hit	hit;
	t_vec3	oc;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(sphere->pos, ray->orig);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - sphere->sphere.radius * sphere->sphere.radius;
	discriminant = b * b - 4 * c;
	if (discriminant < FLT_EPSILON)
		return (hit_miss());
	hit.did_hit = true;
	hit.obj = sphere;
	set_hit(&hit, ray, b, discriminant);
	return (hit);
}

t_hit	hit_miss(void)
{
	return ((t_hit){.did_hit = false, .distance = INFINITY});
}
