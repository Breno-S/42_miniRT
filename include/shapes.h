/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:49:00 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/08 15:53:34 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "core.h"

typedef struct s_ambient
{
	float	i_rate;
	t_color	color;
} t_ambient;

typedef struct s_camera
{
	t_v3	viewport;
	t_v3	normalize_3d;
	int		fov;
} t_camera;

typedef struct s_light
{
	t_v3	center;
	t_v3	brightness;
	t_color	color;
} t_light;

typedef struct s_sphere
{
	t_v3	center;
	t_v3	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_v3	center;
	t_v3	normalize_3d;
	t_color	color;
}	t_plane;

typedef struct s_cilinder
{
	t_v3	center;
	t_v3	axis;
	t_v3	diameter;
	float	height;
	t_color	color;
}	t_plane;


#endif
