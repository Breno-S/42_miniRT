/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:54:17 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/05/28 00:29:15 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "shapes.h"
# include "scene.h"
# include "libft.h"

typedef enum e_ent_type
{
	ambient	= 1,
	camera = 2,
	light = 4
}	t_ent_type;

// PARSER

t_scene	parser(int argc, char **argv);

// READ FILE

bool	check_file(char *file, t_scene *scene);
bool	read_file(int fd, t_scene *scene);
bool	verify_line(char *line, unsigned char *verify_ent, t_scene *scene);

// IMPORT ENTITYS

void	ft_rtlstadd_back(t_rt_list **lst, t_rt_list *new);
int		verify_entity(char *line, int init, int size);

bool	create_entity(char *entity, int type);
bool	create_ambient(char *entity);
bool	create_camera(char *entity);
bool	create_light(char *entity);
bool	create_sphere(char *entity);
bool	create_plane(char *entity);
bool	create_cylinder(char *entity);
bool	create_cone(char *entity);

void	link_entity(t_rt_list *n_rt_list);
bool	verify_mandatory_ent(t_shapes_type type, unsigned char *verify_ent,
			t_scene *scene);

// IMPORT VECS

bool	import_vec3_normalize(char *text, t_vec3 *vec3);
bool	import_color(char *text, t_color *vec3);
bool	import_vec3(char *text, t_vec3 *vec3);
bool	verify_atoi(char *nptr, int n_nbr);
bool	verify_atof(char *nptr, float n_nbr);

// ERRORS

bool	error_msg(int err_type);
bool	error_msg_ii(int err_type);

// CREATE SCENE

bool	create_scene(t_scene *scene);
void	create_scene_aux(t_rt_list *rt_list, t_scene *scene);

#endif
