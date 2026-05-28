/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:56:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 00:27:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt.h"

bool	rt_parse_args(t_rt *rt, int argc, char **argv)
{
	if (!rt || argc != 2)
	{
		error_msg(INVALID_ARG);
		return (false);
	}
	if (check_file(argv[1], &rt->scene))
		return (false);
	if (create_scene(&rt->scene))
		return (false);
	return (true);
}

// t_scene	parser(int argc, char **argv)
// {
// 	t_scene	scene;

// 	scene = (t_scene){0};
// 	if (argc != 2)
// 	{
// 		error_msg(INVALID_ARG);
// 		return ((t_scene){0});
// 	}
// 	if (check_file(argv[1], &scene))
// 		return ((t_scene){0});
// 	if (create_scene(&scene))
// 		return ((t_scene){0});
// 	return (scene);
// }

bool	verify_line(char *line, unsigned char *verify_ent, t_scene *scene)
{
	int	i[2];
	int	type;

	i[0] = 0;
	i[1] = 0;
	type = 0;
	while (ft_isspace(line[i[0]]))
		i[0]++;
	while (line[i[0] + i[1]] && !ft_isspace(line[i[0] + i[1]]))
		i[1]++;
	type = verify_entity(line, i[0], i[1]);
	if (!type || verify_mandatory_ent(type, verify_ent, scene))
		return (1);
	if (type != -1 && create_entity(line, type))
		return (1);
	return (0);
}

bool	verify_mandatory_ent(t_shapes_type type, unsigned char *verify_ent,
	t_scene *scene)
{
	if ((int)type == -1)
		return (0);
	else if (type != AMBIENT && type != CAMERA && type != LIGHT)
	{
		scene->objs_num++;
		return (0);
	}
	else if (type == AMBIENT && !(verify_ent[0] & ambient))
		verify_ent[0] |= ambient;
	else if (type == CAMERA && !(verify_ent[0] & camera))
		verify_ent[0] |= camera;
	else if (type == LIGHT && !(verify_ent[0] & light))
	{
		scene->lights_num++;
		verify_ent[0] |= light;
	}
	else
		return (error_msg_ii(DUP_ENT));
	return (0);
}

int	verify_entity(char *line, int init, int size)
{
	int	flag;
	int	rtn;

	flag = 0;
	rtn = -1;
	if (ft_isspace(line[init + size]))
		flag = 1;
	line[init + size] = 0;
	if (!ft_strcmp(&line[init], "A"))
		rtn = AMBIENT;
	else if (!ft_strcmp(&line[init], "C"))
		rtn = CAMERA;
	else if (!ft_strcmp(&line[init], "L"))
		rtn = LIGHT;
	else if (!ft_strcmp(&line[init], "sp"))
		rtn = SPHERE;
	else if (!ft_strcmp(&line[init], "pl"))
		rtn = PLANE;
	else if (!ft_strcmp(&line[init], "cy"))
		rtn = CYLINDER;
	else if (!ft_strcmp(&line[init], "co"))
		rtn = CONE;
	if (flag == 1)
		line[init + size] = ' ';
	return (rtn);
}
