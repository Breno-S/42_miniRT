/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:02:25 by brensant          #+#    #+#             */
/*   Updated: 2026/05/28 00:21:07 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "ray.h"
# include "vec_math.h"

# define SHADOW_BIAS 0.001f

typedef struct s_obj	t_obj;

typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	t_vec3		reflected;
	t_obj		*obj;
	float		distance;
	bool		did_hit;
}	t_hit;

t_hit	hit_miss(void);
t_hit	hit_sphere(t_ray *ray, t_obj *sphere);
t_hit	hit_plane(t_ray *ray, t_obj *plane);
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder);
t_hit	hit_cone(t_ray *ray, t_obj *cylinder);

#endif // HIT_H
