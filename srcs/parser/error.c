/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:56:10 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/06/12 15:52:43 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	error_msg(int err_type, char *msg)
{
	write(2, "error\n", 6);
	if (err_type)
		write(2, msg, ft_strlen(msg));
	else
		perror("miniRT");
	return (1);
}

bool	warning_msg(int err_type, char *msg)
{
	write(2, "Warning\n", 9);
	if (err_type)
		write(2, msg, ft_strlen(msg));
	else
		perror("miniRT");
	return (1);
}
