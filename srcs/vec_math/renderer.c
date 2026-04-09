/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/04/10 02:37:22 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "color.h"
# include "core.h"
# include "ray.h"
# include "renderer.h"
# include "vec_math.h"

# include <math.h>

/****************************** FOR DEBUG ONLY ********************************/

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	int		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}	t_sphere;

t_sphere sphere = {{0, 0, 4, 1}, 2, (t_color){.hex = 0xFF00FF}};

t_camera camera = {{0, 0, 0, 1}, {0, 0, 1, 1}, 70};

/******************************************************************************/

static void	pixel_put(t_env *env, int x, int y, int color)
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

static void	shade()
{
}

static void	miss()
{
}

/**
 * TODO: remove viewport calculations after I'm done messing about.
 * */
void	renderer_render(t_env *env)
{
	int	x;
	int	y;
	float	vp_width = 2 * tanf(camera.fov * DEG2RAD / 2.0);
	float	vp_height = vp_width * ((float)env->height / env->width);

	t_vec3	vp_w_vec = vec3_new(vp_width, 0, 0);
	t_vec3	vp_h_vec = vec3_new(0, vp_height, 0);

	t_vec3	vp_w_dx = vec3_scale(vp_w_vec, 1.0 / env->width);
	t_vec3	vp_h_dx = vec3_scale(vp_h_vec, 1.0 / env->height);

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			t_vec3 curr_pixel_vec = vec3_add(vec3_scale(vp_w_dx, x), vec3_scale(vp_h_dx, y));

			// Generate ray
			ray_new(camera.pos, vec3_normalize(vec3_sub(curr_pixel_vec, camera.pos)));

			// Get closest collision

			// Compute color at intersection point

			x++;
		}
		y++;
	}
}
