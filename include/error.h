/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:32 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/06 14:32:24 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#define INVALID_ARG "miniRT: Invalid args\n"
#define INVALID_EXT "miniRT: Invalid extension\n"

typedef enum e_type_err
{
	invalid_arg,
	invalid_extension,
	open_err
} t_type_erro;

#endif
