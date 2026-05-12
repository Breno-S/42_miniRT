/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:16 by brensant          #+#    #+#             */
/*   Updated: 2026/05/12 19:36:15 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "core.h"

# include <stdint.h>

# define SPECULAR_STRENGTH 1.0f
# define AMBIENT_STRENGTH 0.3f
# define DIFFUSE_STRENGTH 0.9f
# define SPECULAR_HIGHLIGHT 128.0f

typedef union u_color
{
	uint32_t	hex;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	};
}	t_color;

t_vec4	color_to_vec(t_color color);
t_color	color_from_vec(t_vec4 color);
t_vec4	color_vec_clamp(t_vec4 color);

#endif // COLOR_H
