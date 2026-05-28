/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_ii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:58:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 14:33:04 by rgomes-d         ###   ########.fr       */
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
	link_entity(lst);
	return (0);
}

bool	create_cone(char *entity)
{
	char		**s_ent;
	t_rt_list	*lst;
	float		diameter;

	lst = ft_gc_calloc_root(1, sizeof(*lst), "ent");
	lst->obj.type = CONE;
	s_ent = ft_split_spaces(entity);
	ft_gcfct_arr_register((void **)s_ent, GC_DATA);
	if (ft_size_chrarr(s_ent) != 6)
		return (error_msg(MANY_ARGS));
	if (import_vec3(s_ent[1], &lst->obj.pos) == 1)
		return (1);
	if (import_vec3_normalize(s_ent[2], &lst->obj.cone.axis) == 1)
		return (1);
	diameter = ft_atof(s_ent[3]);
	lst->obj.cone.height = ft_atof(s_ent[4]);
	if (verify_atof(s_ent[3], diameter)
		|| verify_atof(s_ent[4], lst->obj.cone.height))
		return (1);
	lst->obj.cone.radius = diameter / 2.0;
	if (import_color(s_ent[5], &lst->obj.color) == 1)
		return (1);
	lst->obj.intersect = hit_cone;
	link_entity(lst);
	return (0);
}

bool	create_material(char **entity, t_rt_list *lst)
{
	t_mat	*mat;

	mat = ft_gc_calloc_root(1, sizeof(*mat), "obj");
	lst->obj.phong_spec = mat;
	if (!mat)
		return (1);
	if (ft_strcmp(entity[0], "mt"))
		return (1);
	mat->ka = ft_atof(entity[1]);
	mat->kd = ft_atof(entity[2]);
	mat->ks = ft_atof(entity[3]);
	mat->m = ft_atof(entity[4]);
	if (isinf(mat->ka) || isinf(mat->kd) || isinf(mat->ks) || isinf(mat->m))
		return (1);
	if (!ft_check_extension(entity[5], ".xpm"))
		mat->bump_map = save_xpm(entity[5]);
	else if (ft_strnstr(entity[5], "NO_XPM", 99))
		mat->bump_map = NULL;
	else
		return (1);
	return (0);
}

char	*save_xpm(char *file)
{
	int		fd;
	char	*buffer;
	char	*join;
	char	*bump;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		join = ft_strjoin(bump, buffer);
		free(bump);
		free(buffer);
		bump = join;
	}
	close(fd);
	ft_gcfct_register_root(bump, "bump_map");
	return (bump);
}
