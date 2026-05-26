/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_context.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 02:09:15 by brensant          #+#    #+#             */
/*   Updated: 2026/05/26 17:57:12 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CONTEXT_H
# define RAY_CONTEXT_H

# include "vec_math.h"
# include "shapes.h"
# include "scene.h"
# include "ray.h"
# include "mlx_env.h"

typedef struct s_ray_context
{
	t_vec3	orig;

	t_vec3	start;
	t_vec3	dx;
	t_vec3	dy;

	t_ray	ray;
	t_vec3	px;
	t_color	color;
	t_hit	closest_hit;

}	t_ray_context;

#endif // RAY_CONTEXT_H
