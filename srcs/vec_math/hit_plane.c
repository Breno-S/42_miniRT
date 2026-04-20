/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:16:17 by brensant          #+#    #+#             */
/*   Updated: 2026/04/19 23:19:46 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>
#include <float.h>

t_hit	hit_plane(t_ray *ray, t_plane *plane)
{
	t_hit	hit;
	t_vec3	orig_to_point;
	float	denominator;
	float	t;

	denominator = vec3_dot(plane->normal, ray->dir);
	if (fabs(denominator) > FLT_EPSILON)
	{
		orig_to_point = vec3_sub(plane->point, ray->orig);
		t = vec3_dot(orig_to_point, plane->normal) / denominator;
		if (t >= 0)
		{
			hit.did_hit = true;
			hit.point = ray_at(ray, t);
			hit.distance = t;
			// hit.obj = plane;
			return (hit);
		}
	}
	return (hit_miss());
}
