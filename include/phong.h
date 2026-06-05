/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:03:13 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/04 23:48:18 by rgomes-d         ###   ########.fr       */
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

t_vec3	get_color_light(t_light light, t_hit hit, t_ray ray);

t_vec3	get_new_color(float diff, float spec, t_vec3 color_light, t_hit hit);

void	ray_color(t_rt *rt, t_vec3 hit_padded, t_light light, t_vec3 *color);

#endif
