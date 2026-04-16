/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:01:56 by brensant          #+#    #+#             */
/*   Updated: 2026/04/16 13:57:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

static t_hit	get_hit_from_sphere(t_ray *ray, float a, float b, float c)
{
	t_hit	hit;
	float	discriminant;
	float	closest_hit_scalar;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_miss());
	closest_hit_scalar = (-b - sqrt(discriminant)) / 2.0 * a;
	hit.did_hit = true;
	hit.point = ray_at(&ray, closest_hit_scalar);
	hit.distance = vec3_length(vec3_sub(hit.point, ray->orig));
	return (hit);
}

t_hit hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;

	oc = vec3_sub(sphere->center, ray->orig);
	a = vec3_dot(ray->dir, ray->dir);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	return (get_hit_from_sphere(&ray, a, b, c));
}


t_hit	hit_miss(void)
{
	return ((t_hit){.did_hit = false});
}
