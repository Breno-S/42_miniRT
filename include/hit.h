/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:02:25 by brensant          #+#    #+#             */
/*   Updated: 2026/04/16 14:31:37 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

typedef struct s_hit
{
	t_vec3	point;
	float	distance;
	bool	did_hit;
}	t_hit;

t_hit	hit_miss(void);
t_hit	hit_sphere(t_ray *ray, t_sphere *sphere);

#endif // HIT_H
