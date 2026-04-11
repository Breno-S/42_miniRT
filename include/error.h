/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/10 21:13:45 by rgomes-d         ###   ########.fr       */
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

typedef enum e_type_err
{
	invalid_arg,
	invalid_extension,
	open_err,
	miss_ent,
	non_normalize,
	err_color,
	err_fov,
	err_light
}	t_type_erro;

#endif
