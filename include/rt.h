/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:33:22 by brensant          #+#    #+#             */
/*   Updated: 2026/04/28 02:11:04 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "mlx_env.h"
# include "scene.h"

# include <stdbool.h>

typedef struct s_rt
{
	t_mlx_env	mlx_env;
	t_scene		scene;
}	t_rt;

bool	rt_parse_args(t_rt *rt, int argc, char **argv);

bool	rt_mlx_env_setup(t_rt *rt, int width, int height, const char *name);
void	rt_mlx_env_destroy(t_rt *rt);

bool	rt_mlx_env_setup_hooks(t_rt *rt);

#endif // RT_H
