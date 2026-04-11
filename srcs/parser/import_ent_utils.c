/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_ent_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:52:50 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/10 21:23:58 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_color	import_color(char *text)
{
	t_color	vec3;
	char	**c_v3;

	vec3 = (t_color){0};
	if (!text)
		return ((t_color){-1,-1,-1,-1});
	c_v3 = ft_split(text, ',');
	ft_gcfct_arr_register((void **)c_v3, GC_DATA);
	if (ft_size_chrarr(c_v3) != 3)
		return ((t_color){-1,-1,-1,-1});
	vec3.r = ft_atoi(c_v3[0]);
	vec3.g = ft_atoi(c_v3[1]);
	vec3.b = ft_atoi(c_v3[2]);
	if (verify_atoi(c_v3[0], vec3.r) || verify_atoi(c_v3[1], vec3.g)
		|| verify_atoi(c_v3[2], vec3.b))
		return ((t_color){-1,-1,-1,-1});
	if ((vec3.r > 255 || vec3.g > 255 || vec3.b > 255)
		|| (vec3.r < 0 || vec3.g < 0 || vec3.b < 0))
	{
		error_msg(err_color);
		return ((t_color){-1,-1,-1,-1});
	}
	return (vec3);
}

t_v3	import_vec3_normalize(char *text)
{
	t_v3	vec3;
	char	**c_v3;

	vec3 = (t_v3){0};
	if (!text)
		return ((t_v3){-2,-2,-2});
	c_v3 = ft_split(text, ',');
	ft_gcfct_arr_register((void **)c_v3, GC_DATA);
	if (ft_size_chrarr(c_v3) != 3)
		return ((t_v3){-2,-2,-2});
	vec3.x = ft_atof(c_v3[0]);
	vec3.y = ft_atof(c_v3[1]);
	vec3.z = ft_atof(c_v3[2]);
	if ((vec3.x > 1.0 || vec3.y > 1.0 || vec3.z > 1.0)
		|| (vec3.x < -1.0 || vec3.y < -1.0 || vec3.z < -1.0))
	{
		error_msg(non_normalize);
		return ((t_v3){-2,-2,-2});
	}
	return (vec3);
}

t_v3	import_vec3(char *text)
{
	t_v3	vec3;
	char	**c_v3;

	vec3 = (t_v3){0};
	if (!text)
		return ((t_v3){-1,-1,-1});
	c_v3 = ft_split(text, ',');
	ft_gcfct_arr_register((void **)c_v3, GC_DATA);
	if (ft_size_chrarr(c_v3) != 3)
		return ((t_v3){-1,-1,-1});
	vec3.x = ft_atof(c_v3[0]);
	vec3.y = ft_atof(c_v3[1]);
	vec3.z = ft_atof(c_v3[2]);
	return (vec3);
}

void	link_entity(t_rt_list *n_rt_list)
{
	t_root_list	*ent_root;
	t_gc_list	*gc_list;
	t_rt_list	*rt_list;

	ent_root = ft_gc_call_root("ent");
	if (!ent_root)
		return ;
	gc_list = ft_to_gc_list(ent_root->lst->head->content)->content;
	rt_list = (t_rt_list *)gc_list;
	if (rt_list == n_rt_list)
		return ;
	ft_rtlstadd_back(&rt_list, n_rt_list);
	return ;
}

int	create_entity(char *entity, int type)
{
	int	rtn;

	rtn = 1;
	if (type == tp_ambient)
		rtn = create_ambient(entity);
	else if (type == tp_camera)
		rtn = create_camera(entity);
	else if (type == tp_light)
		rtn = create_light(entity);
	else if (type == tp_sphere)
		rtn = create_sphere(entity);
	else if (type == tp_plane)
		rtn = create_plane(entity);
	else if (type == tp_cylinder)
		rtn = create_cylinder(entity);
	return (rtn);
}
