/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:49:00 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/20 19:51:10 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "core.h"
# include "color.h"
# include "vec_math.h"

typedef enum e_shapes_type
{
	AMBIENT	= 1,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_shapes_type;

typedef struct s_ambient
{
	t_shapes_type	type;
	float			i_rate;
	t_color			color;
}	t_ambient;

typedef struct s_camera
{
	t_shapes_type	type;
	t_vec3			pos;
	t_vec3			dir;
	int				fov;
}	t_camera;

typedef struct s_light
{
	t_shapes_type	type;
	t_vec3			pos;
	float			brightness;
	t_color			color;
}	t_light;

typedef struct s_sphere
{
	float			radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3			normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3			axis;
	float			radius;
	float			height;
}	t_cylinder;

typedef struct s_obj
{
	t_shapes_type	type;
	t_vec3			pos;
	t_color			color;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}	t_obj;

typedef struct s_rt_list
{
	union
	{
		t_obj			obj;
		t_camera		camera;
		t_light			light;
		t_ambient		ambient;
	};
	struct s_rt_list	*next;
}	t_rt_list;

#endif
