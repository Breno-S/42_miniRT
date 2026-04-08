/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:58:42 by brensant          #+#    #+#             */
/*   Updated: 2026/04/08 14:07:18 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

typedef struct t_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_env
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_env;

t_env	*env_create(int width, int height);
void	env_destroy(t_env *env);

#endif
