/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:52:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/22 19:31:29 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	create_scene(t_scene *scene)
{
	t_rt_list	*rt_list;
	t_obj		*obj;
	t_light		*light;

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
	create_scene_aux(rt_list, scene);
	return (0);
}

void	create_scene_aux(t_rt_list *rt_list, t_scene *scene)
{
	int	i_light;
	int	i_obj;

	i_light = 0;
	i_obj = 0;
	while (rt_list)
	{
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
	ft_gc_del_root("ent");
	ft_gc_collect();
}
