/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:37:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/02 13:49:09 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_verify_base(char *base)
{
	int	i;
	int	scn_i;

	i = 0;
	while (base[i] != '\0')
	{
		scn_i = 0;
		while (base[scn_i] != '\0')
		{
			if ((base[i] == base[scn_i] && i != scn_i)
				|| (base[scn_i] == '+' || base [scn_i] == '-')
				|| (base[scn_i] <= 32 || base[scn_i] > 126))
				return (0);
			scn_i++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	else
		return (i);
}

int	ft_base_value(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nb_base;
	int	result;
	int	i;
	int	mult;

	nb_base = ft_verify_base(base);
	if (nb_base == 0)
		return (0);
	i = 0;
	mult = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			mult *= -1;
	while (ft_base_value(base, str[i]) != 0 && str[i] != '\0')
		result = (ft_base_value(base, str[i++]) + (result * nb_base));
	return (result * mult);
}
