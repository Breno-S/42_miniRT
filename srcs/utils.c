/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:02:53 by brensant          #+#    #+#             */
/*   Updated: 2026/06/11 00:06:32 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx_env.h"
#include "mlx.h"
#include "utils.h"
#include "rt_error.h"
#include "libft.h"

static bool	verify_new_xpm(t_list *lst, t_mapping *bump);
static void	att_lst_xpm(t_list **lst, t_mapping *bump);

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
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (i < rt->scene.objs_num)
	{
		if (rt->scene.obj[i].phong_spec.b_type & B_COLOR
			&& import_bump_file(&rt->scene.obj[i].phong_spec.color,
				rt->mlx.mlx_ptr, &lst))
			rt->scene.obj[i].phong_spec.b_type
				= (rt->scene.obj[i].phong_spec.b_type & ~B_COLOR);
		if (rt->scene.obj[i].phong_spec.b_type & B_NORMAL
			&& import_bump_file(&rt->scene.obj[i].phong_spec.normal,
				rt->mlx.mlx_ptr, &lst))
			rt->scene.obj[i].phong_spec.b_type
				= (rt->scene.obj[i].phong_spec.b_type & ~B_NORMAL);
		if (rt->scene.obj[i].phong_spec.b_type & B_BUMP
			&& import_bump_file(&rt->scene.obj[i].phong_spec.bump,
				rt->mlx.mlx_ptr, &lst))
			rt->scene.obj[i].phong_spec.b_type
				= (rt->scene.obj[i].phong_spec.b_type & ~B_BUMP);
		i++;
	}
}

bool	import_bump_file(t_mapping *bump, void *mlx, t_list **lst)
{
	if (verify_new_xpm(*lst, bump))
	{
		bump[0].img = mlx_xpm_file_to_image(
				mlx, bump[0].filename, &bump->width, &bump->height);
		bump->img_addr = mlx_get_data_addr(bump->img, &bump->bpp,
				&bump->size_line, &bump->endian);
		if (!bump[0].img)
		{
			if (bump[0].b_type & B_NORMAL)
				bump[0].b_type = (bump[0].b_type & ~B_NORMAL);
			if (bump[0].b_type & B_COLOR)
				bump[0].b_type = (bump[0].b_type & ~B_COLOR);
			if (bump[0].b_type & B_BUMP)
				bump[0].b_type = (bump[0].b_type & ~B_BUMP);
			error_msg(1, M_IMP_XPM);
			ft_putendl_fd(bump[0].filename, 2);
			ft_putendl_fd(M_DEFAULT, 2);
			return (1);
		}
		att_lst_xpm(lst, bump);
	}
	return (0);
}

static void	att_lst_xpm(t_list **lst, t_mapping *bump)
{
	t_list	*n_lst;

	n_lst = NULL;
	if (!*lst)
		*lst = ft_gcfct_register(ft_lstnew(bump), GC_DATA)->content;
	else
	{
		n_lst = ft_gcfct_register(ft_lstnew(bump), GC_DATA)->content;
		ft_lstadd_back(lst, n_lst);
	}
}

static bool	verify_new_xpm(t_list *lst, t_mapping *bump)
{
	t_list		*nv;
	t_mapping	txt;

	nv = lst;
	while (nv)
	{
		txt = *(t_mapping *)nv->content;
		if (ft_strnstr(txt.filename, bump->filename, ft_strlen(bump->filename)))
		{
			bump->img = txt.img;
			bump->width = txt.width;
			bump->height = txt.height;
			bump->endian = txt.endian;
			bump->bpp = txt.bpp;
			bump->size_line = txt.size_line;
			bump->img_addr = txt.img_addr;
			return (false);
		}
		nv = nv->next;
	}
	return (true);
}
