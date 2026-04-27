/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:38:59 by brensant          #+#    #+#             */
/*   Updated: 2026/04/28 02:01:14 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENV_H
# define MLX_ENV_H

typedef struct s_mlx_env
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_mlx_env;

#endif // MLX_ENV_H
