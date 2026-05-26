/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:55:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/26 15:24:09 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "math.h"

bool	verify_atoi(char *nptr, int n_nbr)
{
	int	i;

	if (!nptr)
		return (1);
	i = 0;
	while (ft_isspace(nptr[i]) || nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (!n_nbr && nptr[i] != '0' && ft_isdigit(nptr[i]))
		return (error_msg_ii(ERR_CONV));
	return (0);
}

bool	verify_atof(char *nptr, float n_nbr)
{
	int	i;

	if (!nptr)
		return (1);
	i = 0;
	while (ft_isspace(nptr[i]) || nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (!n_nbr && nptr[i] != '0' && ft_isdigit(nptr[i]))
		return (error_msg_ii(ERR_CONV));
	if (isinf(n_nbr) == 1)
		return (error_msg_ii(ERR_CONV));
	return (0);
}
