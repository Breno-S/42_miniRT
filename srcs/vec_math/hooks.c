/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:07:08 by brensant          #+#    #+#             */
/*   Updated: 2026/04/28 02:04:10 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>

#include "mlx.h"
#include "rt.h"

static int	handle_keypress(int keysym, t_rt *rt)
{
	if (keysym == 0xff1b)
		rt_mlx_env_destroy(rt);
	return (0);
}

static int	close_window(t_rt *rt)
{
	rt_mlx_env_destroy(rt);
	return (0);
}

bool	rt_mlx_env_setup_hooks(t_rt *rt)
{
	t_mlx_env	*mlx;

	if (!rt || !rt->mlx_env.win_ptr)
		return (false);
	mlx = &rt->mlx_env;
	mlx_hook(mlx->win_ptr, 2, (1L << 0), handle_keypress, &mlx);
	mlx_hook(mlx->win_ptr, 17, 0, close_window, &mlx);
	return (true);
}
