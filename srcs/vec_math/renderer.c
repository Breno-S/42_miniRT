/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:18:38 by brensant          #+#    #+#             */
/*   Updated: 2026/04/16 22:07:43 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "color.h"
# include "core.h"
# include "stdio.h"
# include "mlx.h"
# include "ray.h"
# include "renderer.h"
# include "vec_math.h"
# include "shapes.h" /* INCLUIR DPS */

# include <math.h>

/****************************** FOR DEBUG ONLY ********************************/

t_sphere sphere = {{0, 0, 3, 1}, 1, (t_color){.hex = 0xcc0040}};

t_plane plane = {{5, 0, 0, 1}, {-1, 0, 0, 1}, (t_color){.hex = 0xffffff}};
t_plane plane2 = {{0, -1, 0, 1}, {0, 1, 0, 1}, (t_color){.hex = 0xFFff10}};
t_plane plane3 = {{-5, 0, 0, 1}, {-1, 0, 0, 1}, (t_color){.hex = 0xffffff}};

t_camera camera = {{0, 0, 0, 1}, {0, 0, 1, 1}, 70};

t_light light = {{0,5,2,1}, 1.0, (t_color){.hex = 0xFFFFFF}};

t_ambient ambient = {0.0, (t_color){.hex = 0xFFFFFF}};

float	hit_plane(t_plane plane, t_ray ray, float *t);
static t_color	ray_to_plane(float t, t_ray ray, t_plane *plane);
static t_color	ray_to_sphere(float t, t_ray ray, t_sphere *sphere);

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

float hit_sphere(t_sphere *sphere, t_ray ray, float *t)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(sphere->center, ray.orig);
	a = vec3_dot(ray.dir, ray.dir);
	b = -2.0 * vec3_dot(ray.dir, oc);
	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b -4 * a * c;
	if (discriminant <= 0)
		return (-1.0);
	if (t[0] < 0 || ((-b - sqrt(discriminant)) / 2.0 * a) < t[0])
		t[0] = (-b - sqrt(discriminant)) / 2.0 * a;
	else
		return (-1.0);
	return (t[0]);
}
float	hit_plane(t_plane plane, t_ray ray, float *t)
{
	t_vec3	p0l0;
	float	denom;
	float	t_plane;

	denom = vec3_dot(plane.normal, ray.dir);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = vec3_sub(plane.center, ray.orig);
		t_plane = vec3_dot(p0l0, plane.normal) / denom;
		if (t_plane > 0 && (t[0] < 0 || t_plane < t[0]))
			t[0] = t_plane;
		else
			return (-1.0);
		return (t[0]);
	}
	return (-1);
}

static t_color ray_color(t_sphere *sphere, t_ray ray)
{
	int flag;
	float t;

	t = -1;
	flag = -1;
	if (hit_plane(plane, ray, &t) != -1)
		flag = tp_plane;
	if (hit_plane(plane2, ray, &t) != -1)
		flag = tp_plane+1;
	if (hit_plane(plane3, ray, &t) != -1)
		flag = tp_camera;
	if (hit_sphere(sphere, ray, &t) != -1)
		flag = tp_sphere;
	if (t > 0.0 && flag == tp_plane)
		return(ray_to_plane(t, ray, &plane));
	else if (t > 0.0 && flag == tp_sphere)
		return(ray_to_sphere(t, ray, sphere));
	else if (t > 0.0 && flag == tp_cylinder)
		return(ray_to_plane(t, ray, &plane2));
	else if (t > 0.0 && flag == tp_camera)
		return(ray_to_plane(t, ray, &plane3));
	return (t_color){.hex = 0x202020}; // Cor do background (cinza escuro)
}

static t_color	ray_to_plane(float t, t_ray ray, t_plane *plane)
{

	t_vec3 hit_point = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	// Vetor da Luz (exemplo de luz direcional)
	// t_vec3 light_dir = vec3_normalize(light.center); // Luz vindo do canto
	// Vetor da Luz (exemplo de luz pontual)
	t_vec3 light_dir = vec3_normalize(vec3_sub(light.center, hit_point));
	// Produto escalar para a intensidade (0.0 a 1.0)
	// float intensity = (vec3_dot(normal, light_dir) * light.brightness) + ambient.i_rate;
	// calculando dot (0.0 a 1.0)
	float dot = fabs(vec3_dot(plane->normal, light_dir)) * light.brightness;
	printf("%f\n", dot);
	// calculando intensity levando ambient em consideração. tirando a diferença do ambient e multiplicando pelo dot
	float intensity = ambient.i_rate + (1.0 - ambient.i_rate) * dot;
	if (intensity < 0) intensity = 0; // Não iluminar o que está "atrás"
	// Aplicar intensidade na cor (exemplo simples)
	return (color_from_vec(vec3_scale(color_to_vec(plane->color), intensity)));
}

static t_color	ray_to_sphere(float t, t_ray ray, t_sphere *sphere)
{
	t_vec3 hit_point = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	// Vetor Normal
	t_vec3 normal = vec3_normalize(vec3_sub(hit_point, sphere->center));
	// Vetor da Luz (exemplo de luz direcional)
	// t_vec3 light_dir = vec3_normalize(light.center); // Luz vindo do canto
	// Vetor da Luz (exemplo de luz pontual)
	t_vec3 light_dir = vec3_normalize(vec3_sub(light.center, hit_point));
	// Produto escalar para a intensidade (0.0 a 1.0)
	// float intensity = (vec3_dot(normal, light_dir) * light.brightness) + ambient.i_rate;
	// calculando dot (0.0 a 1.0)
	float dot = vec3_dot(normal, light_dir) * light.brightness;
	// calculando intensity levando ambient em consideração. tirando a diferença do ambient e multiplicando pelo dot
	float intensity = ambient.i_rate + (1.0 - ambient.i_rate) * dot;
	if (intensity < 0) intensity = 0; // Não iluminar o que está "atrás"
	// Aplicar intensidade na cor (exemplo simples)
	return (color_from_vec(vec3_scale(color_to_vec(sphere->color), intensity)));
}

static void	build_image(t_env *env)
{
}

t_ray_context	get_ray_context(t_env *env, t_camera *camera)
{
	t_ray_context	rc;
	float			vp_width;
	float			vp_height;

	vp_width = 2 * tanf(camera->fov * DEG2RAD / 2.0);
	vp_height = vp_width * ((float)env->height / env->width);
	rc.vp_w_vec = vec3_new(vp_width, 0, 0);
	rc.vp_h_vec = vec3_new(0, -vp_height, 0);
	rc.vp_fd_vec = vec3_new(0, 0, FOCAL_DISTANCE);
	rc.vp_dx = vec3_scale(rc.vp_w_vec, 1.0 / env->width);
	rc.vp_dy = vec3_scale(rc.vp_h_vec, 1.0 / env->height);
	rc.vp_start = vec3_add(camera->pos, rc.vp_fd_vec);
	rc.vp_start = vec3_add(rc.vp_start, vec3_negate(vec3_scale(rc.vp_w_vec,
		0.5)));
	rc.vp_start = vec3_add(rc.vp_start, vec3_negate(vec3_scale(rc.vp_h_vec,
		0.5)));
	return (rc);
}
/**
 * TODO: remove viewport calculations after I'm done messing about.
 * */
void	renderer_render(t_env *env)
{
	t_ray_context	rc;

	rc = get_ray_context(env, &camera);

	// Init camera and viewport
	// float	vp_width = 2 * tanf(camera.fov * DEG2RAD / 2.0);
	// float	vp_height = vp_width * ((float)env->height / env->width);
	// int		focal_distance = 1; // z

	// t_vec3	vp_w_vec = vec3_new(vp_width, 0, 0);
	// t_vec3	vp_h_vec = vec3_new(0, -vp_height, 0);
	// t_vec3	vp_fd_vec = vec3_new(0, 0, focal_distance);

	// t_vec3	vp_dx = vec3_scale(vp_w_vec, 1.0 / env->width);
	// t_vec3	vp_dy = vec3_scale(vp_h_vec, 1.0 / env->height);

	// t_vec3	vp_upper_left = vec3_add(camera.pos, vp_fd_vec);
	// vp_upper_left = vec3_add(vp_upper_left, vec3_negate(vec3_scale(vp_w_vec, 0.5)));
	// vp_upper_left = vec3_add(vp_upper_left, vec3_negate(vec3_scale(vp_h_vec, 0.5)));

	// TODO: make build_image function
	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	t_vec3	curr_pixel_vec;
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			curr_pixel_vec = vec3_add(rc.vp_start, vec3_scale(rc.vp_dx, x));
			curr_pixel_vec = vec3_add(curr_pixel_vec, vec3_scale(rc.vp_dy, y));

			// Generate ray
			t_ray ray = ray_new(camera.pos, vec3_normalize(vec3_sub(curr_pixel_vec, camera.pos)));

			// Get closest collision
			// Compute color at intersection point

			t_color color = ray_color(&sphere, ray);

			pixel_put(env, x, y, color.hex);

			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}
