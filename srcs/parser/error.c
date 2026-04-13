/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:56:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/13 18:54:47 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	error_msg(int err_type)
{
	write(2, "error\n", 6);
	if (err_type == invalid_arg)
		write(2, INVALID_ARG, ft_strlen(INVALID_ARG));
	else if (err_type == invalid_extension)
	{
		write(2, INVALID_EXT, ft_strlen(INVALID_EXT));
		return (-1);
	}
	else if (err_type == miss_ent)
		write(2, MISS_ENT, ft_strlen(MISS_ENT));
	else if (err_type == non_normalize)
		write(2, NON_NORMALIZE, ft_strlen(NON_NORMALIZE));
	else if (err_type == err_color)
		write(2, ERR_COLOR, ft_strlen(ERR_COLOR));
	else if (err_type == err_fov)
		write(2, ERR_FOV, ft_strlen(ERR_FOV));
	else if (err_type == err_light)
		write(2, ERR_LIGHT, ft_strlen(ERR_LIGHT));
	else if (err_type == many_args)
		write(2, MANY_ARG, ft_strlen(MANY_ARG));
	else if (err_type == size_vec)
		write(2, SIZE_VEC, ft_strlen(SIZE_VEC));
	else
		perror("miniRT");
	return (1);
}

int	error_msg_ii(int err_type)
{
	write(2, "error\n", 6);
	if (err_type == err_conv)
		write(2, ERR_CONV, ft_strlen(ERR_CONV));
	else if (err_type == dup_ent)
		write(2, DUP_ENT, ft_strlen(DUP_ENT));
	else
		perror("miniRT");
	return (1);
}
