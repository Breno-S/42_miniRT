/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:58:42 by brensant          #+#    #+#             */
/*   Updated: 2026/04/10 21:19:07 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stdint.h>

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

#endif
