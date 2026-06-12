/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:07:08 by brensant          #+#    #+#             */
/*   Updated: 2026/06/12 16:56:06 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "rt.h"

static void	finish_images(t_rt rt)
{
	t_list	*xpm;

	xpm = rt.xpm;
	if (rt.scene.lights)
	{
		while (xpm)
		{
			mlx_destroy_image(rt.mlx.mlx_ptr, ((t_mapping *)xpm->content)->img);
			xpm = xpm->next;
		}
	}
}

static int	handle_keypress(int keysym, t_rt *rt)
{
	if (keysym == 0xff1b)
	{
		finish_images(*rt);
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
