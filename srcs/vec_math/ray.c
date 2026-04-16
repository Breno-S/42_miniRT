/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:41:53 by brensant          #+#    #+#             */
/*   Updated: 2026/04/16 13:37:24 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_new(t_vec3 origin, t_vec3 direction)
{
	return ((t_ray){.orig = origin, .dir = direction});
}

t_vec3	ray_at(t_ray *ray, float t)
{
	return (vec3_add(ray->orig, vec3_scale(ray->dir, t)));
}
