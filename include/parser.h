/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:54:17 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/20 17:02:44 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "shapes.h"
# include "libft.h"

typedef enum e_ent_type
{
	ambient	= 1,
	camera = 2,
	light = 4
}	t_ent_type;

int		parser(int ac, char **av);
int		error_msg(int err_type);
int		error_msg_ii(int err_type);
void	ft_rtlstadd_back(t_rt_list **lst, t_rt_list *new);
int		check_file(char *file);
int		read_file(int fd);
int		verify_line(char *line, unsigned char *verify_ent);
int		verify_entity(char *line, int init, int size);
int		create_entity(char *entity, int type);
int		create_ambient(char *entity);
int		create_camera(char *entity);
int		create_light(char *entity);
int		create_sphere(char *entity);
int		create_plane(char *entity);
int		create_cylinder(char *entity);
void	link_entity(t_rt_list *n_rt_list);
int		import_vec3_normalize(char *text, t_vec3 *vec3);
int		import_color(char *text, t_color *vec3);
int		import_vec3(char *text, t_vec3 *vec3);
int		verify_mandatory_ent(t_shapes_type type, unsigned char *verify_ent);
int		verify_atoi(char *nptr, int n_nbr);
float	verify_atof(char *nptr, float n_nbr);

#endif
