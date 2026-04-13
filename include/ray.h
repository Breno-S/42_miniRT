/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:26:07 by brensant          #+#    #+#             */
/*   Updated: 2026/04/09 14:31:46 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec_math.h"

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

t_ray	ray_new(t_vec3 origin, t_vec3 direction);

#endif // RAY_H
