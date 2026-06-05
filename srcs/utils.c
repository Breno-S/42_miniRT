/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:02:53 by brensant          #+#    #+#             */
/*   Updated: 2026/06/04 22:38:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx_env.h"
#include "mlx.h"
#include "utils.h"
#include "rt_error.h"
#include "libft.h"

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

void	create_textures(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->scene.objs_num)
	{
		if (rt->scene.obj[i].phong_spec.b_type & COLOR
			&& import_bump_file(&rt->scene.obj[i].phong_spec.color,
				rt->mlx.mlx_ptr))
			rt->scene.obj[i].phong_spec.b_type
				= (rt->scene.obj[i].phong_spec.b_type & ~COLOR);
		if (rt->scene.obj[i].phong_spec.b_type & NORMAL
			&& import_bump_file(&rt->scene.obj[i].phong_spec.normal,
				rt->mlx.mlx_ptr))
			rt->scene.obj[i].phong_spec.b_type
				= (rt->scene.obj[i].phong_spec.b_type & ~NORMAL);
		i++;
	}
}

bool	import_bump_file(t_bump *bump, void *mlx)
{
	bump[0].img = mlx_xpm_file_to_image(
			mlx, bump[0].filename, &bump->width, &bump->heigth);
	if (!bump[0].img)
	{
		if (bump[0].b_type & NORMAL)
			bump[0].b_type = (bump[0].b_type & ~NORMAL);
		if (bump[0].b_type & COLOR)
			bump[0].b_type = (bump[0].b_type & ~COLOR);
		error_msg_ii(IMP_XPM);
		ft_putendl_fd(bump[0].filename, 2);
		return (1);
	}
	return (0);
}
