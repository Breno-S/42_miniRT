/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:56:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/01 15:54:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdio.h"

int parser(int ac, char **av)
{
	printf("oi");
}
inline int verify_norm_point(double point)
{
	return(point > 1);
}

inline int verify_norm_color(int color)
{
	return(color > 255);
}
