/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:16 by brensant          #+#    #+#             */
/*   Updated: 2026/04/08 17:52:41 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "core.h"

# include <stdint.h>

typedef union u_color
{
	uint64_t	hex;
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
