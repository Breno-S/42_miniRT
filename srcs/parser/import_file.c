/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:59:44 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/10 21:04:35 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	read_file(int fd)
{
	unsigned char	verify_ent;
	char			*file;

	verify_ent = 0;
	file = get_next_line(fd);
	while (file)
	{
		if (verify_line(file, &verify_ent))
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
	return (error_msg(miss_ent));
}

int	check_file(char *file)
{
	int	fd;

	fd = -1;
	if (ft_check_extension(file, ".rt"))
		return (error_msg(invalid_extension));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg(open_err);
	return (fd);
}
