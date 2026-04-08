/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:43:03 by brensant          #+#    #+#             */
/*   Updated: 2026/04/08 14:24:57 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "mlx.h"

#include <stdlib.h>

t_env	*env_create(int width, int height)
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (!env)
		return ((void *)0);
	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, width, height, "miniRT");
	env->img_ptr = mlx_new_image(env->mlx_ptr, width, height);
	env->img_addr = mlx_get_data_addr(env->img_ptr, &env->bpp, &env->line_len,
			&env->endian);
	if (!env->mlx_ptr || !env->win_ptr || !env->img_ptr || !env->img_addr)
	{
		env_destroy(env);
		return ((void *)0);
	}
	return (env);
}

void	env_destroy(t_env *env)
{
	free(env->mlx_ptr);
	free(env->win_ptr);
	free(env->img_addr);
	free(env->img_ptr);
	free(env);
}
