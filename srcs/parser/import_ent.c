/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:51:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/08 17:39:09 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_camera(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->camera.type = CAMERA;
	lst->camera.matrix = matrix_identity();
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(1, M_MANY_ARG));
	if (import_vec3(s_ent[1], &lst->camera.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->camera.dir) == 1)
		return (1);
	lst->camera.fov = ft_atoi(s_ent[3]);
	if (verify_atoi(s_ent[3]))
		return (1);
	if (lst->camera.fov > 180 || lst->camera.fov < 0)
		return (error_msg(1, M_ERR_FOV));
	link_entity(lst);
	return (0);
}

bool	create_light(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->light.type = LIGHT;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4 && ft_size_chrarr(s_ent) != 3)
		return (error_msg(1, M_MANY_ARG));
	if (import_vec3(s_ent[1], &lst->light.pos) == 1)
		return (1);
	lst->light.brightness = ft_atof(s_ent[2]);
	if (verify_atof(s_ent[2], lst->light.brightness)
		|| lst->light.brightness > 1.0 || lst->light.brightness < 0.0)
		return (error_msg(1, M_ERR_LIGHT));
	if (ft_size_chrarr(s_ent) == 4)
	{
		if (import_color(s_ent[3], &lst->light.color) == 1)
			return (1);
		lst->light.vec_color = color_to_vec(lst->light.color);
	}
	link_entity(lst);
	return (0);
}

bool	create_ambient(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->ambient.type = AMBIENT;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 3)
		return (error_msg(1, M_MANY_ARG));
	lst->ambient.i_rate = ft_atof(s_ent[1]);
	if (lst->ambient.i_rate > 1.0 || lst->ambient.i_rate < 0.0)
		return (error_msg(1, M_ERR_LIGHT));
	if (import_color(s_ent[2], &lst->ambient.color) == 1)
		return (1);
	lst->ambient.vec_color = color_to_vec(lst->ambient.color);
	link_entity(lst);
	return (0);
}
