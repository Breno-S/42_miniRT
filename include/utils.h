/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:06:52 by brensant          #+#    #+#             */
/*   Updated: 2026/06/03 17:56:07 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mlx_env.h"

void	pixel_put(t_mlx_env *env, int x, int y, int color);

void	create_textures(t_rt *rt);

bool	import_bump_file(t_bump *bump, void *mlx);

#endif // UTILS_H
