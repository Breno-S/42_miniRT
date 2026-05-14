/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:42:52 by brensant          #+#    #+#             */
/*   Updated: 2026/05/14 16:34:36 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include "core.h"

typedef t_vec4	t_vec3;

typedef struct s_matrix
{
	float	m[4][4];
}	t_matrix;

t_vec3		vec3_new(float x, float y, float z);

float		vec3_length(t_vec3 v);
t_vec3		vec3_normalize(t_vec3 v);
t_vec3		vec3_negate(t_vec3 v);
t_vec3		vec3_scale(t_vec3 v, float scalar);

t_vec3		vec3_add(t_vec3 u, t_vec3 v);
t_vec3		vec3_sub(t_vec3 u, t_vec3 v);
float		vec3_dot(t_vec3 u, t_vec3 v);
t_vec3		vec3_cross(t_vec3 u, t_vec3 v);
t_vec3		vec3_mult(t_vec3 u, t_vec3 v);
float		vec3_distance(t_vec3 u, t_vec3 v);

t_vec3		vec3_transform(t_vec3 v, t_matrix mat);

t_matrix	matrix_identity(void);
t_matrix	matrix_mult(t_matrix *left, t_matrix *right);

#endif // VEC_MATH_H
