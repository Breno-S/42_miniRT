/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/22 19:31:21 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define M_INVALID_ARG	"miniRT: Invalid args\n"
# define M_INVALID_EXT	"miniRT: Invalid extension\n"
# define M_MISS_ENT "miniRT: A entity is missing (ambient, camera, or light).\n"
# define M_NON_NORMALIZE "miniRT: Vec. not normalized (between '-1' and '1').\n"
# define M_ERR_COLOR "miniRT: Color is not within a valid range (0–255).\n"
# define M_ERR_FOV "miniRT: FOV is out of range (0–180).\n"
# define M_ERR_LIGHT "miniRT: Amb. rate or bright is out of range (0–1).\n"
# define M_MANY_ARG "miniRT: Too many arguments in entity.\n"
# define M_SIZE_VEC "miniRT: Invalid vector size.\n"
# define M_ERR_CONV "miniRT: Invalid number conversion (overflow or inf.).\n"
# define M_DUP_ENT "miniRT: Dup. entity declaration (ambient, cam or light).\n"

typedef enum e_type_err
{
	INVALID_ARG,
	INVALID_EXTENSION,
	OPEN_ERR,
	MISS_ENT,
	NON_NORMALIZE,
	ERR_COLOR,
	ERR_FOV,
	ERR_LIGHT,
	MANY_ARGS,
	SIZE_VEC,
	ERR_CONV,
	DUP_ENT,
}	t_type_erro;

#endif
