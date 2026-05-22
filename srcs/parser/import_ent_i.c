/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:51:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/22 17:01:24 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "hit.h"

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
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->camera.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->camera.dir) == 1)
		return (1);
	if (lst->camera.dir.x == -2)
		return (1);
	lst->camera.fov = ft_atoi(s_ent[3]);
	if (lst->camera.fov > 180 || lst->camera.fov < 0)
		return (error_msg(ERR_FOV));
	if (verify_atoi(s_ent[3], lst->camera.fov))
		return (1);
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
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->light.pos) == 1)
		return (1);
	lst->light.brightness = ft_atof(s_ent[2]);
	if (verify_atof(s_ent[2], lst->light.brightness)
		|| lst->light.brightness > 1.0 || lst->light.brightness < 0.0)
		return (error_msg(ERR_LIGHT));
	link_entity(lst);
	return (0);
}

bool	create_sphere(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;
	float		diameter;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = SPHERE;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	diameter = ft_atof(s_ent[2]);
	if (verify_atof(s_ent[2], diameter))
		return (1);
	lst->obj.sphere.radius = diameter / 2.0;
	if (import_color(s_ent[3], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_sphere;
	link_entity(lst);
	return (0);
}

bool	create_plane(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = PLANE;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4)
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->obj.plane.normal) == 1)
		return (1);
	if (import_color(s_ent[3], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_plane;
	link_entity(lst);
	return (0);
}

bool	create_cylinder(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;
	float		diameter;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = CYLINDER;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 6)
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->obj.cylinder.axis) == 1)
		return (1);
	diameter = ft_atof(s_ent[3]);
	lst->obj.cylinder.height = ft_atof(s_ent[4]);
	if (verify_atof(s_ent[3], diameter)
		|| verify_atof(s_ent[4], lst->obj.cylinder.height))
		return (1);
	lst->obj.cylinder.radius = diameter / 2.0;
	if (import_color(s_ent[5], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_cylinder;
	link_entity(lst);
	return (0);
}
