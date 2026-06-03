/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:16 by brensant          #+#    #+#             */
/*   Updated: 2026/06/03 19:55:09 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "core.h"

# include <stdint.h>

# define C_KA 0.1f
# define C_KD 0.9f
# define C_KS 1.0f
# define C_M  32.0f
# define C_R  0.0f

# define D1 1.0f
# define D2 0.000005f
# define D3 0.000001f

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
