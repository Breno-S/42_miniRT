/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:58:42 by brensant          #+#    #+#             */
/*   Updated: 2026/04/10 02:08:52 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define HEIGHT 400
# define WIDTH 400

# define PI 3.14159265358979323846f

# define DEG2RAD (PI / 180.0f)
# define RAD2DEG (180.0f / PI)

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
