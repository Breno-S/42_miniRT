/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:01:48 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 16:45:31 by rgomes-d         ###   ########.fr       */
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
