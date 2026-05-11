/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:42:52 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 15:45:24 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include "core.h"

typedef t_vec4	t_vec3;

typedef struct s_matrix
{
	float	r0[4];
	float	r1[4];
	float	r2[4];
	float	r3[4];
}	t_matrix;

t_vec3	vec3_new(float x, float y, float z);

float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_negate(t_vec3 v);
t_vec3	vec3_scale(t_vec3 v, float scalar);

t_vec3	vec3_add(t_vec3 u, t_vec3 v);
t_vec3	vec3_sub(t_vec3 u, t_vec3 v);
float	vec3_dot(t_vec3 u, t_vec3 v);
t_vec3	vec3_cross(t_vec3 u, t_vec3 v);
t_vec3	vec3_mult(t_vec3 u, t_vec3 v);
float	vec3_distance(t_vec3 u, t_vec3 v);

t_vec3	vec3_transform(t_vec3 v, t_matrix m);

#endif // VEC_MATH_H
