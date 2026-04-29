/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:07:08 by brensant          #+#    #+#             */
/*   Updated: 2026/04/29 19:33:51 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>

#include "mlx.h"
#include "rt.h"
#include "libft.h"

static int	handle_keypress(int keysym, t_rt *rt)
{
	if (keysym == 0xff1b)
	{
		rt_mlx_destroy(rt);
		ft_gc_end();
		exit(0);
	}
	return (0);
}

static int	close_window(t_rt *rt)
{
	rt_mlx_destroy(rt);
	ft_gc_end();
	exit(0);
	return (0);
}

bool	rt_mlx_env_setup_hooks(t_rt *rt)
{
	t_mlx_env	*mlx;

	if (!rt || !rt->mlx.win_ptr)
		return (false);
	mlx = &rt->mlx;
	mlx_hook(mlx->win_ptr, 2, (1L << 0), handle_keypress, rt);
	mlx_hook(mlx->win_ptr, 17, 0, close_window, rt);
	return (true);
}
