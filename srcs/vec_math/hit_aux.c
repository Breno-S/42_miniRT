/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:48:20 by brensant          #+#    #+#             */
/*   Updated: 2026/06/08 15:14:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

#include <math.h>

t_hit	hit_miss(void)
{
	return ((t_hit){.did_hit = false, .distance = INFINITY});
}
