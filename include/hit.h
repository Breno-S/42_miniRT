/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:02:25 by brensant          #+#    #+#             */
/*   Updated: 2026/06/08 20:34:52 by brensant         ###   ########.fr       */
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
	t_vec3		base_color;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		hit_padded;
	t_vec3		reflected;
	t_obj		*obj;
	float		distance;
	bool		did_hit;
}	t_hit;

void	set_uv_coords(t_hit *hit);

t_vec3	handle_surface_color(t_hit *hit);
t_vec3	get_surface_color(t_hit *hit);
t_vec3	get_surface_chk(t_hit *hit);
t_vec3	get_surface_normal(t_hit *hit);

t_hit	hit_miss(void);
t_hit	hit_sphere(t_ray *ray, t_obj *sphere);
t_hit	hit_plane(t_ray *ray, t_obj *plane);
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder);
t_hit	hit_cone(t_ray *ray, t_obj *cylinder);

#endif // HIT_H
