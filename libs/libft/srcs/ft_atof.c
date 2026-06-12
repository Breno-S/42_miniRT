/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:45:51 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/13 13:45:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nptr)
{
	int		i;
	double	result;
	double	utils[2];

	i = 0;
	result = 0.0;
	utils[0] = 1;
	utils[1] = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			utils[1] *= -1;
	while (ft_isdigit(nptr[i]))
		result = (nptr[i++] - '0') + (result * 10);
	if (nptr[i] == '.')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		result = (nptr[i++] - '0') + (result * 10);
		utils[0] *= 10;
	}
	return ((result / utils[0]) * utils[1]);
}
