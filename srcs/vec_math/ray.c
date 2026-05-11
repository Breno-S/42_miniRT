/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:41:53 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 15:45:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec_math.h"

t_ray	ray_new(t_vec3 origin, t_vec3 direction)
{
	return ((t_ray){.orig = origin, .dir = vec3_normalize(direction)});
}

t_vec3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(ray->orig, vec3_scale(ray->dir, t)));
}
