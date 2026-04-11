/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:56:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/10 21:10:34 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdio.h"

int	parser(int ac, char **av)
{
	int	fd;

	if (ac > 2 || ac < 2)
		return (error_msg(invalid_arg));
	fd = check_file(av[1]);
	if (fd == -1)
		return (1);
	if (read_file(fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	verify_line(char *line, unsigned char *verify_ent)
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
	if (!type || verify_mandatory_ent(type, verify_ent))
		return (1);
	if (create_entity(line, type))
		return (1);
	return (0);
}

int	verify_mandatory_ent(t_shpes_type type, unsigned char *verify_ent)
{
	if (type != tp_ambient && type != tp_camera && type != tp_light)
		return (0);
	else if (type == tp_ambient && !(verify_ent[0] & ambient))
		verify_ent[0] |= ambient;
	else if (type == tp_camera && !(verify_ent[0] & camera))
		verify_ent[0] |= camera;
	else if (type == tp_light && !(verify_ent[0] & light))
		verify_ent[0] |= light;
	else
		return (1);
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
		rtn = tp_ambient;
	else if (!ft_strcmp(&line[init], "C"))
		rtn = tp_camera;
	else if (!ft_strcmp(&line[init], "L"))
		rtn = tp_light;
	else if (!ft_strcmp(&line[init], "sp"))
		rtn = tp_sphere;
	else if (!ft_strcmp(&line[init], "pl"))
		rtn = tp_plane;
	else if (!ft_strcmp(&line[init], "cy"))
		rtn = tp_cylinder;
	if (flag == 1)
		line[init + size] = ' ';
	return (rtn);
}
