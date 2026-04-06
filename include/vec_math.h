/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:42:52 by brensant          #+#    #+#             */
/*   Updated: 2026/04/06 16:45:46 by brensant         ###   ########.fr       */
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

float	vec3_length(t_vec3 v);
t_vec3	vec3_negate(t_vec3 v);
t_vec3	vec3_scale(t_vec3 v, float scalar);
t_vec3	vec3_add(t_vec3 u, t_vec3 v);
t_vec3	vec3_sub(t_vec3 u, t_vec3 v);
float	vec3_dot(t_vec3 u, t_vec3 v);
t_vec3	vec3_cross(t_vec3 u, t_vec3 v);
t_vec3	vec3_transform(t_vec3 v, t_matrix m);

#endif // VEC_MATH_H
