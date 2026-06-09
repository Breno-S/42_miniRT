/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:06:52 by brensant          #+#    #+#             */
/*   Updated: 2026/06/09 17:43:55 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mlx_env.h"

void	pixel_put(t_mlx_env *env, int x, int y, int color);

void	create_textures(t_rt *rt);

bool	import_bump_file(t_mapping *bump, void *mlx);

#endif // UTILS_H
