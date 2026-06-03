/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:52:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/03 20:20:57 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_scene(t_scene *scene)
{
	t_rt_list	*rt_list;
	t_obj		*obj;
	t_light		*light;
	t_mat		material;

	material = generic_material();
	rt_list = ft_to_gc_list(
			ft_gc_call_root("ent")->lst->head->content)->content;
	if (!rt_list)
		return (1);
	obj = ft_gc_calloc_root(scene->objs_num, sizeof(*obj), "scene");
	light = ft_gc_calloc_root(scene->lights_num, sizeof(*light), "scene");
	if (!obj || !light)
		return (error_msg(99));
	scene->obj = obj;
	scene->lights = light;
	if (create_scene_aux(rt_list, scene, material))
		return (error_msg(99));
	ft_gc_del_root("ent");
	ft_gc_collect();
	return (0);
}

bool	create_scene_aux(t_rt_list *rt_list, t_scene *scene, t_mat mat)
{
	int			i_light;
	int			i_obj;

	i_light = 0;
	i_obj = 0;
	while (rt_list)
	{
		if (rt_list->obj.type > 3)
			rt_list->obj.color_vec = color_to_vec(rt_list->obj.color);
		if (rt_list->obj.type > 3 && !rt_list->obj.phong_spec.has_mat)
			rt_list->obj.phong_spec = mat;
		if (rt_list->obj.type == AMBIENT)
			scene->ambient = rt_list->ambient;
		else if (rt_list->obj.type == CAMERA)
			scene->cam = rt_list->camera;
		else if (rt_list->obj.type == LIGHT)
			scene->lights[i_light++] = rt_list->light;
		else
			scene->obj[i_obj++] = rt_list->obj;
		rt_list = rt_list->next;
	}
	while (i_obj-- > 0)
		scene->obj[i_obj].ka_final = scene->ambient.i_rate
			* scene->obj[i_obj].phong_spec.ka;
	return (0);
}

t_mat	generic_material(void)
{
	t_mat	material;

	material = (t_mat){0};
	material.has_mat = 1;
	material.ka = C_KA;
	material.kd = C_KD;
	material.ks = C_KS;
	material.m = C_M;
	material.r = C_R;
	// material.b_type = CHK;
	return (material);
}
