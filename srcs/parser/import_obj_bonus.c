/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_obj_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:25:02 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/03 19:28:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_cone(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = CONE;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 6 && ft_size_chrarr(s_ent) != 14)
		return (error_msg(MANY_ARGS));
	if (ft_size_chrarr(s_ent) == 14 && create_material(&s_ent[6], &lst))
		return (1);
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->obj.cone.axis) == 1)
		return (1);
	if (create_cone_aux(s_ent, lst))
		return (1);
	return (0);
}

bool	create_cone_aux(char **s_ent, t_rt_list *lst)
{
	lst->obj.cone.radius = ft_atof(s_ent[3]) / 2.0;
	lst->obj.cone.height = ft_atof(s_ent[4]) * 2;
	lst->obj.pos = vec3_add(lst->obj.pos,
			vec3_scale(lst->obj.cone.axis, lst->obj.cone.height / 2.0));
	if (verify_atof(s_ent[3], lst->obj.cone.radius)
		|| verify_atof(s_ent[4], lst->obj.cone.height))
		return (1);
	if (import_color(s_ent[5], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_cone;
	link_entity(lst);
	return (0);
}
