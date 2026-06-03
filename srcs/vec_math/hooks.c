/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:07:08 by brensant          #+#    #+#             */
/*   Updated: 2026/06/03 19:02:02 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>

#include "mlx.h"
#include "rt.h"
#include "libft.h"

static void	finish_images(t_rt rt)
{
	int	i;

	i = 0;
	if (rt.scene.lights)
	{
		while (i < rt.scene.objs_num)
		{
			if (rt.scene.obj[i].phong_spec.b_type & NORMAL)
				mlx_destroy_image(rt.mlx.mlx_ptr,
					rt.scene.obj[i].phong_spec.normal.img);
			if (rt.scene.obj[i].phong_spec.b_type & COLOR)
				mlx_destroy_image(rt.mlx.mlx_ptr,
					rt.scene.obj[i].phong_spec.color.img);
			i++;
		}
	}
}

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
	finish_images(*rt);
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
