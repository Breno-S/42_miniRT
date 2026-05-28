/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:56:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 15:12:22 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	error_msg(int err_type)
{
	write(2, "error\n", 6);
	if (err_type == INVALID_ARG)
		write(2, M_INVALID_ARG, ft_strlen(M_INVALID_ARG));
	else if (err_type == INVALID_EXTENSION)
		write(2, M_INVALID_EXT, ft_strlen(M_INVALID_EXT));
	else if (err_type == MISS_ENT)
		write(2, M_MISS_ENT, ft_strlen(M_MISS_ENT));
	else if (err_type == NON_NORMALIZE)
		write(2, M_NON_NORMALIZE, ft_strlen(M_NON_NORMALIZE));
	else if (err_type == ERR_COLOR)
		write(2, M_ERR_COLOR, ft_strlen(M_ERR_COLOR));
	else if (err_type == ERR_FOV)
		write(2, M_ERR_FOV, ft_strlen(M_ERR_FOV));
	else if (err_type == ERR_LIGHT)
		write(2, M_ERR_LIGHT, ft_strlen(M_ERR_LIGHT));
	else if (err_type == MANY_ARGS)
		write(2, M_MANY_ARG, ft_strlen(M_MANY_ARG));
	else if (err_type == SIZE_VEC)
		write(2, M_SIZE_VEC, ft_strlen(M_SIZE_VEC));
	else
		perror("miniRT");
	return (1);
}

bool	error_msg_ii(int err_type)
{
	write(2, "error\n", 6);
	if (err_type == ERR_CONV)
		write(2, M_ERR_CONV, ft_strlen(M_ERR_CONV));
	else if (err_type == DUP_ENT)
		write(2, M_DUP_ENT, ft_strlen(M_DUP_ENT));
	else if (err_type == NBR_NORM)
		write(2, M_NBR_NORM, ft_strlen(M_NBR_NORM));
	else
		perror("miniRT");
	return (1);
}
