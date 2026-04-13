/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/13 18:54:14 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define INVALID_ARG	"miniRT: Invalid args\n"
# define INVALID_EXT	"miniRT: Invalid extension\n"
# define MISS_ENT "miniRT: A entity is missing (ambient, camera, or light).\n"
# define NON_NORMALIZE "miniRT: Vector not normalized (between '-1' and '1').\n"
# define ERR_COLOR "miniRT: Color is not within a valid range (0–255).\n"
# define ERR_FOV "miniRT: FOV is out of range (0–180).\n"
# define ERR_LIGHT "miniRT: Amb. rate or bright is out of range (0–1).\n"
# define MANY_ARG "miniRT: Too many arguments in entity.\n"
# define SIZE_VEC "miniRT: Invalid vector size.\n"
# define ERR_CONV "miniRT: Invalid number conversion (overflow or infinity).\n"
# define DUP_ENT "Error: Dup. entity declaration (ambient, camera, or light).\n"

typedef enum e_type_err
{
	invalid_arg,
	invalid_extension,
	open_err,
	miss_ent,
	non_normalize,
	err_color,
	err_fov,
	err_light,
	many_args,
	size_vec,
	err_conv,
	dup_ent,
}	t_type_erro;

#endif
