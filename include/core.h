/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:58:42 by brensant          #+#    #+#             */
/*   Updated: 2026/04/23 14:36:44 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stdbool.h>

# define HEIGHT 1000
# define WIDTH 1000

# define PI 3.14159265358979323846f

# define DEG2RAD 0.017453292519943295769f
# define RAD2DEG 57.29577951308232087680f

# define FOCAL_DISTANCE 1.0f

# define BACKGROURD_COLOR 0x202020

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
	int		width;
	int		height;
}	t_env;

t_env	*env_create(int width, int height, const char *name);
void	env_destroy(t_env *env);

#endif
