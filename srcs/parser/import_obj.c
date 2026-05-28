/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:23:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 18:51:53 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_sphere(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;
	float		diameter;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = SPHERE;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 4 && ft_size_chrarr(s_ent) != 10)
		return (error_msg(MANY_ARGS));
	if (ft_size_chrarr(s_ent) == 10 && create_material(&s_ent[4], lst))
		return (1);
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
	if (ft_size_chrarr(s_ent) != 4 && ft_size_chrarr(s_ent) != 10)
		return (error_msg(MANY_ARGS));
	if (ft_size_chrarr(s_ent) == 10 && create_material(&s_ent[4], lst))
		return (1);
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

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = CYLINDER;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 6 && ft_size_chrarr(s_ent) != 12)
		return (error_msg(MANY_ARGS));
	if (ft_size_chrarr(s_ent) == 12 && create_material(&s_ent[6], lst))
		return (1);
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->obj.cylinder.axis) == 1)
		return (1);
	lst->obj.cylinder.radius = ft_atof(s_ent[3]) / 2.0;
	lst->obj.cylinder.height = ft_atof(s_ent[4]);
	if (verify_atof(s_ent[3], lst->obj.cylinder.radius)
		|| verify_atof(s_ent[4], lst->obj.cylinder.height))
		return (error_msg_ii(ERR_CONV));
	if (import_color(s_ent[5], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_cylinder;
	link_entity(lst);
	return (0);
}
