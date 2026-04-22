/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 02:09:15 by brensant          #+#    #+#             */
/*   Updated: 2026/04/22 19:46:01 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "vec_math.h"
# include "shapes.h"

typedef struct s_ray_context
{
	t_vec3	orig;

	t_vec3	vp_w_vec;
	t_vec3	vp_h_vec;
	t_vec3	vp_fd_vec;

	t_vec3	vp_start;
	t_vec3	vp_dx;
	t_vec3	vp_dy;
}	t_ray_context;

typedef struct s_renderer
{
}	t_renderer;

void			renderer_render(t_env *env, t_scene scene);
t_ray_context	get_ray_context(t_env *env, t_camera *camera);

#endif // RENDERER_H
