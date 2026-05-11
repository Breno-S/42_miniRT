/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:58:42 by brensant          #+#    #+#             */
/*   Updated: 2026/05/11 19:09:24 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stdbool.h>

# define HEIGHT 720
# define WIDTH 1228

# define PI 3.14159265358979323846f

# define DEG2RAD 0.017453292519943295769f
# define RAD2DEG 57.29577951308232087680f

# define FOCAL_DISTANCE 0.6f

# define BACKGROURD_COLOR 0x000000

typedef struct t_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

#endif
