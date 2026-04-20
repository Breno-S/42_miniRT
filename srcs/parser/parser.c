/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:56:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/20 17:02:44 by brensant         ###   ########.fr       */
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

int	verify_mandatory_ent(t_shapes_type type, unsigned char *verify_ent)
{
	if (type != AMBIENT && type != CAMERA && type != LIGHT)
		return (0);
	else if (type == AMBIENT && !(verify_ent[0] & ambient))
		verify_ent[0] |= ambient;
	else if (type == CAMERA && !(verify_ent[0] & camera))
		verify_ent[0] |= camera;
	else if (type == LIGHT && !(verify_ent[0] & light))
		verify_ent[0] |= light;
	else
		return (error_msg_ii(dup_ent));
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
	if (flag == 1)
		line[init + size] = ' ';
	return (rtn);
}
