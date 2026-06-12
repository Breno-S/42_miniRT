/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:38:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/12 16:05:09 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_material(char **entity, t_rt_list **lst)
{
	t_mat	mat;

	mat = (t_mat){0};
	mat.has_mat = 1;
	if (ft_strcmp(entity[0], "mt"))
		return (1);
	mat.ka = ft_atof(entity[1]);
	mat.kd = ft_atof(entity[2]);
	mat.ks = ft_atof(entity[3]);
	mat.m = ft_atof(entity[4]);
	mat.kr = ft_atof(entity[5]);
	if ((mat.ka > 1.0 || mat.ks > 1.0 || mat.kd > 1.0 || mat.kr > 1.0)
		|| (mat.ka < 0.0 || mat.ks < 0.0 || mat.kd < 0.0 || mat.kr < 0.0))
		return (error_msg(1, M_NBR_NORM));
	if (verify_atof(entity[1], mat.ka) || verify_atof(entity[2], mat.kd)
		|| verify_atof(entity[3], mat.ks) || verify_atof(entity[4], mat.m)
		|| verify_atof(entity[5], mat.kr))
		return (1);
	import_normal_map(entity[6], &mat);
	import_bump_map(entity[7], &mat);
	import_color_map(entity[8], &mat);
	lst[0]->obj.phong_spec = mat;
	return (0);
}

void	import_bump_map(char *filename, t_mat *mat)
{
	if (!ft_check_extension(filename, ".xpm"))
	{
		mat->b_type |= B_BUMP;
		mat->bump.b_type |= B_BUMP;
		mat->bump.filename = ft_gcfct_register_root(
				(void *)ft_strdup(filename), "bmp");
	}
	else if (!ft_strnstr(filename, "NON_BUMP", 99))
	{
		warning_msg(1, M_NORMAL_ERR);
		ft_putendl_fd(M_DEFAULT, 2);
	}
}

void	import_normal_map(char *filename, t_mat *mat)
{
	if (!ft_check_extension(filename, ".xpm"))
	{
		mat->b_type |= B_NORMAL;
		mat->normal.b_type |= B_NORMAL;
		mat->normal.filename = ft_gcfct_register_root(
				(void *)ft_strdup(filename), "bmp");
	}
	else if (!ft_strnstr(filename, "NON_NORMAL", 99))
	{
		warning_msg(1, M_NORMAL_ERR);
		ft_putendl_fd(M_DEFAULT, 2);
	}
}

void	import_color_map(char *filename, t_mat *mat)
{
	if (!ft_check_extension(filename, ".xpm"))
	{
		mat->b_type |= B_COLOR;
		mat->color.b_type |= B_COLOR;
		mat->color.filename = ft_gcfct_register_root(
				(void *)ft_strdup(filename), "bmp");
	}
	else if (ft_strnstr(filename, "CHK", 99))
	{
		mat->b_type |= B_CHK;
		mat->color.b_type |= B_CHK;
	}
	else if (ft_strnstr(filename, "NORMAL_COLOR", 99))
	{
		mat->b_type |= B_NORMAL_COLOR;
		mat->color.b_type |= B_NORMAL_COLOR;
	}
	else if (!ft_strnstr(filename, "NON_COLOR", 99))
	{
		warning_msg(1, M_BMP_ERR);
		ft_putendl_fd(M_DEFAULT, 2);
	}
}
