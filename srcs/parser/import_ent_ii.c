/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_ii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:58:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/22 19:31:05 by rgomes-d         ###   ########.fr       */
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
	link_entity(lst);
	return (0);
}
