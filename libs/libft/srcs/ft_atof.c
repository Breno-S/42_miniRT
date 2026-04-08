/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:45:51 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/08 13:08:30 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double ft_atof(const char *nptr)
{
	int i;
	double result[2];
	double multiplier;
	double divisor;

	i = 0;
	result[0] = 0;
	result[1] = 0;
	multiplier = 1;
	divisor = 10.0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			multiplier *= -1;
	while (ft_isdigit(nptr[i]))
		result[0] = (nptr[i++] - '0') + (result[0] * 10);
	if (nptr[i] == '.')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		result[1] += (nptr[i++] - '0') / divisor;
		divisor *= 10.0;
	}
	return ((result[0] + result[1]) * multiplier);
}
