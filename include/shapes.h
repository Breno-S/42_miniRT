/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:49:00 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/09 19:35:51 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H

#include "core.h"

typedef enum e_shpes_type
{
	tp_ambient	= 1,
	tp_camera = 2,
	tp_light = 3,
	tp_sphere = 4,
	tp_plane = 5,
	tp_cylinder = 6,
}	t_shpes_type;

typedef struct s_ambient
{
	float i_rate;
	t_color color;
} t_ambient;

typedef struct s_camera
{
	t_v3 viewport;
	t_v3 normalize_3d;
	int fov;
} t_camera;

typedef struct s_light
{
	t_v3 center;
	float brightness;
	t_color color;
} t_light;

typedef struct s_sphere
{
	t_v3 center;
	t_v3 diameter;
	t_color color;
} t_sphere;

typedef struct s_plane
{
	t_v3 center;
	t_v3 normalize_3d;
	t_color color;
} t_plane;

typedef struct s_cylinder
{
	t_v3 center;
	t_v3 axis;
	t_v3 diameter;
	float height;
	t_color color;
} t_cylinder;

typedef union s_ent
{
	t_cylinder cylinder;
	t_sphere sphere;
	t_plane plane;
	t_camera camera;
	t_light light;
	t_ambient ambient;
} t_ent;

typedef struct s_rt_list
{
	t_shpes_type type;
	t_ent ent;
	struct s_rt_list *next;
} t_rt_list;

#endif
