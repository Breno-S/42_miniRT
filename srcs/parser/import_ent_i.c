/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:51:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/16 18:55:01 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	create_camera(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->type = tp_camera;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(many_args));
	if (import_vec3(s_ent[1], &lst->ent.camera.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->ent.camera.dir) == 1)
		return (1);
	lst->ent.camera.fov = ft_atoi(s_ent[3]);
	if (lst->ent.camera.fov > 180 || lst->ent.camera.fov < 0)
		return (error_msg(err_fov));
	if (verify_atoi(s_ent[3], lst->ent.camera.fov))
		return (1);
	link_entity(lst);
	return (0);
}

int	create_light(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->type = tp_light;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4 && ft_size_chrarr(s_ent) != 3)
		return (error_msg(many_args));
	if (import_vec3(s_ent[1], &lst->ent.light.center) == 1)
		return (1);
	lst->ent.light.brightness = ft_atof(s_ent[2]);
	if (verify_atof(s_ent[2], lst->ent.light.brightness)
		|| lst->ent.light.brightness > 1.0 || lst->ent.light.brightness < 0.0)
		return (error_msg(err_light));
	link_entity(lst);
	return (0);
}

int	create_sphere(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->type = tp_sphere;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(many_args));
	if (import_vec3(s_ent[1], &lst->ent.sphere.center) == 1)
		return (1);
	lst->ent.sphere.radius = ft_atof(s_ent[2]);
	if (verify_atof(s_ent[2], lst->ent.sphere.radius))
		return (1);
	if (import_color(s_ent[3], &lst->ent.sphere.color) == 1)
		return (1);
	link_entity(lst);
	return (0);
}

int	create_plane(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->type = tp_plane;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(many_args));
	if (import_vec3(s_ent[1], &lst->ent.plane.center) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->ent.plane.normal) == 1)
		return (1);
	if (import_color(s_ent[3], &lst->ent.plane.color) == 1)
		return (1);
	link_entity(lst);
	return (0);
}

int	create_cylinder(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->type = tp_cylinder;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 6)
		return (error_msg(many_args));
	if (import_vec3(s_ent[1], &lst->ent.cylinder.center) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->ent.cylinder.axis) == 1)
		return (1);
	lst->ent.cylinder.diameter = ft_atof(s_ent[3]);
	lst->ent.cylinder.height = ft_atof(s_ent[4]);
	if (verify_atof(s_ent[3], lst->ent.cylinder.diameter)
		|| verify_atof(s_ent[4], lst->ent.cylinder.height))
		return (1);
	if (import_color(s_ent[5], &lst->ent.cylinder.color) == 1)
		return (1);
	link_entity(lst);
	return (0);
}
