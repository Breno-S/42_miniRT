/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:59:44 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/22 19:30:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	read_file(int fd, t_scene *scene)
{
	unsigned char	verify_ent;
	char			*file;

	verify_ent = 0;
	file = get_next_line(fd);
	while (file)
	{
		if (verify_line(file, &verify_ent, scene))
		{
			free(file);
			get_next_line(-1);
			return (1);
		}
		free(file);
		file = get_next_line(fd);
	}
	if (verify_ent & ambient && verify_ent & camera && verify_ent & light)
		return (0);
	return (error_msg(MISS_ENT));
}

bool	check_file(char *file, t_scene *scene)
{
	int	fd;

	fd = -1;
	if (ft_check_extension(file, ".rt"))
		return (error_msg(INVALID_EXTENSION));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(OPEN_ERR));
	if (read_file(fd, scene))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
