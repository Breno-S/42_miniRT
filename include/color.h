/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:31:16 by brensant          #+#    #+#             */
/*   Updated: 2026/04/06 16:46:30 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "core.h"

# include <stdint.h>

typedef t_vec4	t_color;

uint32_t	color_to_integer(t_color color);
uint32_t	color_from_integer(uint32_t integer);

#endif // COLOR_H
