/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:55:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 19:14:27 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	verify_atoi(char *nptr, int n_nbr)
{
	int			i;
	int			nbr_prev;
	long long	result;
	int			multiplier;

	i = 0;
	result = 0;
	multiplier = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			multiplier *= -1;
	while (ft_isdigit(nptr[i]))
	{
		result = (nptr[i++] - '0') + (result * 10);
		nbr_prev = result * (long long)multiplier;
		if (nbr_prev != (nbr_prev * multiplier))
			return (1);
	}
	if ((nptr[i] && !ft_isdigit(nptr[i])))
		return (error_msg_ii(ERR_CONV));
	return (0);
}

bool	verify_atof(char *nptr, float n_nbr)
{
	int		i;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
		i++;
	if (nptr[i] == '.')
		i++;
	while (ft_isdigit(nptr[i]))
		i++;
	if (isinf(n_nbr) == 1 || (nptr[i] && !ft_isdigit(nptr[i])))
		return (error_msg_ii(ERR_CONV));
	return (0);
}
