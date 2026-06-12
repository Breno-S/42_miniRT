/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:49:00 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/12 14:43:30 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "core.h"
# include "color.h"
# include "hit.h"
# include "vec_math.h"

typedef enum e_shapes_type
{
	AMBIENT	= 1,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_shapes_type;

typedef enum e_btype
{
	B_CHK			= 1 << 0,
	B_NORMAL		= 1 << 1,
	B_BUMP			= 1 << 2,
	B_COLOR			= 1 << 3,
	B_NORMAL_COLOR	= 1 << 4
}	t_btype;

typedef struct s_ambient
{
	t_shapes_type	type;
	float			i_rate;
	t_color			color;
	t_vec3			vec_color;
}	t_ambient;

typedef struct s_camera
{
	t_shapes_type	type;
	t_vec3			pos;
	t_vec3			dir;
	int				fov;
	t_matrix		matrix;
}	t_camera;

typedef struct s_light
{
	t_shapes_type	type;
	t_vec3			pos;
	float			brightness;
	t_color			color;
	t_vec3			vec_color;
	float			to_light;
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

typedef struct s_mapping
{
	t_btype	b_type;
	char	*filename;
	void	*img;
	char	*img_addr;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_mapping;

typedef t_cylinder	t_cone;

typedef struct s_mat
{
	bool			has_mat;
	float			ka;
	float			kd;
	float			ks;
	float			m;
	float			kr;
	unsigned char	b_type;
	t_mapping		normal;
	t_mapping		bump;
	t_mapping		color;
}	t_mat;

typedef struct s_obj
{
	t_shapes_type	type;
	t_vec3			pos;
	t_color			color;
	t_vec3			color_vec;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	};
	t_mat			phong_spec;
	float			ka_final;
	t_hit			(*intersect)(t_ray *, struct s_obj *);
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

#endif // SHAPES_H
