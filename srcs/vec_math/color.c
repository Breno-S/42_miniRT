/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:04:04 by brensant          #+#    #+#             */
/*   Updated: 2026/04/07 15:12:14 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/**
 * TODO: check if alpha is needed in the final value.
 */
uint32_t	color_to_rgb(t_color color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	// uint8_t	a;

	r = color.x;
	g = color.y;
	b = color.z;
	// a = color.w;
	return ((r << 16) | (g << 8) | b);
}

t_color	color_from_rgb(uint32_t rgb)
{
	return ((t_color){
			.x = rgb & 0xFF0000,
			.y = rgb & 0x00FF00,
			.z = rgb & 0xF000FF});
}
