/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:02:25 by brensant          #+#    #+#             */
/*   Updated: 2026/06/02 12:58:18 by brensant         ###   ########.fr       */
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
	float		uv[2];
	t_vec3		point;
	t_vec3		normal;
	t_vec3		reflected;
	t_obj		*obj;
	float		distance;
	bool		did_hit;
}	t_hit;

void	set_uv_coords(t_hit *hit);

t_hit	get_closest_collision(t_ray *ray, t_obj *list, int list_size);
t_hit	hit_miss(void);
t_hit	hit_sphere(t_ray *ray, t_obj *sphere);
t_hit	hit_plane(t_ray *ray, t_obj *plane);
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder);
t_hit	hit_cone(t_ray *ray, t_obj *cylinder);

#endif // HIT_H
