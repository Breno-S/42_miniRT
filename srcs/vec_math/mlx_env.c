/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:43:03 by brensant          #+#    #+#             */
/*   Updated: 2026/04/29 15:58:46 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "mlx.h"
#include "rt.h"

#include <stdlib.h>

void	rt_mlx_destroy(t_rt *rt)
{
	t_mlx_env	*mlx;

	if (!rt)
		return ;
	mlx = &rt->mlx;
	if (mlx->img_addr)
		free(mlx->img_addr);
	if (mlx->img_ptr)
		free(mlx->img_ptr);
	if (mlx->win_ptr)
		free(mlx->win_ptr);
	if (mlx->mlx_ptr)
		free(mlx->mlx_ptr);
	free(mlx);
}

bool	rt_mlx_setup(t_rt *rt, int width, int height, const char *name)
{
	t_mlx_env	*mlx;

	if (!rt)
		return (false);
	mlx = &rt->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, (char *)name);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
	mlx->img_addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	if (!mlx->mlx_ptr || !mlx->win_ptr || !mlx->img_ptr || !mlx->img_addr
		|| !rt_mlx_env_setup_hooks(rt))
	{
		rt_mlx_destroy(rt);
		return (false);
	}
	mlx->width = width;
	mlx->height = height;
	return (true);
}
