/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/08 15:03:00 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H

# include <stdbool.h>

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
# define M_NBR_NORM "miniRT: nbr not normalized (between '0' and '1').\n"
# define M_IMP_XPM "miniRT: unable to load XPM file (missing or invalid): "
# define M_BMP_ERR "miniRT: color map invalid (not a .xpm file or CHK)\n"
# define M_NORMAL_ERR "miniRT: normal map invalid (not a .xpm file)\n"

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
	NBR_NORM,
	NORMAL_ERR,
	BMP_ERR,
	IMP_XPM,
}	t_type_erro;

// ERRORS

bool		error_msg(int err_type);
bool		error_msg_ii(int err_type);

#endif
