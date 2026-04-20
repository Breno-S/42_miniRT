/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:01:48 by brensant          #+#    #+#             */
/*   Updated: 2026/04/20 19:41:35 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shapes.h"

typedef struct s_scene
{
	t_camera	cam;
	t_ambient	ambient;
	t_light		*lights;
	t_obj		*obj;
	int			objs_num;
	int			lights_num;
}	t_scene;

#endif // SCENE_H
