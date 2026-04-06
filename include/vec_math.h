/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:42:52 by brensant          #+#    #+#             */
/*   Updated: 2026/04/06 15:56:42 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_matrix
{
	float	r0[4];
	float	r1[4];
	float	r2[4];
	float	r3[4];
}	t_matrix;

t_vec4	vec3_negate(t_vec4 v);
t_vec4	vec3_scale(t_vec4 v, float scalar);
t_vec4	vec3_add(t_vec4 u, t_vec4 v);
t_vec4	vec3_sub(t_vec4 u, t_vec4 v);
float	vec3_dot(t_vec4 u, t_vec4 v);
t_vec4	vec3_cross(t_vec4 u, t_vec4 v);
t_vec4	vec3_transform(t_vec4 v, t_matrix m);

#endif // VEC_MATH_H
