/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:03:13 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/09 17:45:23 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
# define PHONG_H

# include "vec_math.h"
# include "shapes.h"
# include "scene.h"
# include "ray.h"
# include "rt.h"
# include "mlx_env.h"

t_color	blend_color(t_color color1, t_color color2, float kr);

t_vec3	get_color_light(t_light light, t_hit hit, t_ray ray);

t_vec3	get_new_color(float diff, float spec, t_vec3 color_light, t_hit hit);

t_color	ray_trace(t_rt *rt, int depth);

#endif
