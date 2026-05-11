/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_ii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:58:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/11 19:34:37 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_ambient(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->ambient.type = AMBIENT;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 3)
		return (error_msg(MANY_ARGS));
	lst->ambient.i_rate = ft_atof(s_ent[1]);
	if (lst->ambient.i_rate > 1.0 || lst->ambient.i_rate < 0.0)
		return (error_msg(ERR_LIGHT));
	if (import_color(s_ent[2], &lst->ambient.color) == 1)
		return (1);
	lst->ambient.vec_color = color_to_vec(lst->ambient.color);
	lst->ambient.vec_color = vec3_scale(lst->ambient.vec_color,
		lst->ambient.i_rate);
	link_entity(lst);
	return (0);
}
