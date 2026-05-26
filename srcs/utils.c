/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:02:53 by brensant          #+#    #+#             */
/*   Updated: 2026/05/26 17:34:11 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pixel_put(t_mlx_env *env, int x, int y, int color)
{
	char	*addr;
	int		i;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	addr = env->img_addr + (y * env->line_len + x * env->bpp / 8);
	i = env->bpp - 8;
	while (i >= 0)
	{
		if (env->endian != 0)
			*addr = (color >> i) & 0xFF;
		else
			*addr = (color >> (env->bpp - 8 - i)) & 0xFF;
		addr++;
		i -= 8;
	}
}
