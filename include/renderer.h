/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 02:09:15 by brensant          #+#    #+#             */
/*   Updated: 2026/04/28 02:00:43 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "vec_math.h"
# include "shapes.h"
# include "scene.h"
# include "rt.h"

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

void			renderer_render(t_mlx_env *mlx, t_scene scene);
t_ray_context	get_ray_context(t_mlx_env *mlx, t_camera *camera);

#endif // RENDERER_H
