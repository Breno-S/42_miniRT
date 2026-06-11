/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:02:25 by brensant          #+#    #+#             */
/*   Updated: 2026/06/10 19:34:20 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "ray.h"
# include "vec_math.h"

# define SHADOW_BIAS 0.001f

typedef struct s_obj		t_obj;
typedef struct s_mapping	t_mapping;

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

void	handle_texture_maps(t_hit *hit);
void	apply_normal_map(t_hit *hit, t_vec3 tg, t_vec3 btg);
void	apply_bump_map(t_hit *hit, t_vec3 tg, t_vec3 btg);

t_vec3	handle_surface_color(t_hit *hit);
t_vec3	get_map_value(t_hit *hit, t_mapping *bump);
t_vec3	get_surface_chk(t_hit *hit);
t_vec3	get_surface_normal(t_hit *hit);

t_hit	hit_miss(void);
t_hit	hit_sphere(t_ray *ray, t_obj *sphere);
t_hit	hit_plane(t_ray *ray, t_obj *plane);
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder);
t_hit	hit_cone(t_ray *ray, t_obj *cylinder);

#endif // HIT_H
