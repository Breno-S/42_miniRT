/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:39:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/01 19:30:05 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include "core.h"
#include <math.h>

// normaliza a luz;

#define HEIGHT 1000
#define WIDTH 1000

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_sphere
{
	t_vec3 vec;
	double r;
}	t_sphere;

int color_dot (t_vec3 color, double dot);
int color_dot_amb(t_vec3 color, double dot, double ambient);

int main(int ac, char **av)
{
	printf("it's our miniRT. %s %d", av[0], ac);
	fflush(0);

	void *mlx;
    void *win;
	double dot;
	double len_l;
	t_vec3 act;
	t_vec3 d;
	double pd;
	double ambient;
	t_vec3	color;
	t_vec3	rec;
	t_vec3	color2;
	t_vec3	color3;
	t_vec3 normal;
	t_vec3 light;
	t_vec3 norm_light;
	t_sphere sphere;
	t_sphere sphere2;
	int i = 0;
	int i2 = 0;
	sphere.vec = (t_vec3){-0.75, 0, 0};
	sphere2.vec = (t_vec3){0.75, 0, 0};
	rec = (t_vec3){0.2, 0.3, 1};
	sphere.r = 0.2;
	sphere2.r = 0.2;

	act = (t_vec3){0};
	light = (t_vec3){0, 1, 1};
	norm_light = (t_vec3){0};
	len_l = sqrt(light.x * light.x + light.y * light.y + light.z * light.z);
	norm_light.x =light.x / len_l;
	norm_light.y =light.y / len_l;
	norm_light.z =light.z / len_l;
	color = (t_vec3){255,150,25};
	color2 = (t_vec3){150,25,255};
	color3 = (t_vec3){255,255,255};
	ambient = 0.15;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT , "Minha Janela");

	printf("\nit's our miniRT. %f %d", sphere.r, ac);
	fflush(0);

	while (i < HEIGHT)
	{
		i2 = 0;
		act.y = 1.0 - ((2.0 * i) / HEIGHT);
		while (i2 < WIDTH)
		{
			act.x = ((2.0 * i2) / WIDTH) - 1 ;

			// ponto - luz / || (ponto - luz)2 ||

			//dot = (normal.x * light.x) + (normal.y * light.y) + (normal.z * light.z);
			if ((((act.x - sphere.vec.x) * (act.x - sphere.vec.x)) +
				((act.y - sphere.vec.y) * (act.y - sphere.vec.y))) <= sphere.r * sphere.r)
					{
						d.y = act.y - sphere.vec.y;
						normal.y = d.y / sphere.r;
						d.x = act.x - sphere.vec.x;
						pd = d.x * d.x + d.y * d.y;
						act.z = sqrt(sphere.r * sphere.r - pd);
						normal.z = act.z /sphere.r;
						norm_light.x = light.x - act.x;
						norm_light.y = light.y - act.y;
						norm_light.z = light.z - act.z;
						len_l = sqrt(norm_light.x * norm_light.x + norm_light.y * norm_light.y + norm_light.z * norm_light.z);
						norm_light.x = norm_light.x / len_l;
						norm_light.y = norm_light.y / len_l;
						norm_light.z = norm_light.z / len_l;
						normal.x = d.x / sphere.r;
						dot = (normal.x * norm_light.x) + (normal.y * norm_light.y) + (normal.z * norm_light.z);
						if (dot < 0)
							dot = 0;
						mlx_pixel_put(mlx, win, i2, i,color_dot_amb(color, dot, ambient));
					}
			else if ((((act.x - sphere2.vec.x) * (act.x - sphere2.vec.x)) +
				((act.y - sphere2.vec.y) * (act.y - sphere2.vec.y))) <= sphere2.r * sphere2.r)
					{
						d.y = act.y - sphere2.vec.y;
						normal.y = d.y / sphere2.r;
						d.x = act.x - sphere2.vec.x;
						pd = d.x * d.x + d.y * d.y;
						act.z = sqrt(sphere2.r * sphere2.r - pd);
						normal.z = act.z /sphere2.r;
						norm_light.x = light.x - act.x;
						norm_light.y = light.y - act.y;
						norm_light.z = light.z - act.z;
						len_l = sqrt(norm_light.x * norm_light.x + norm_light.y * norm_light.y + norm_light.z * norm_light.z);
						norm_light.x = norm_light.x / len_l;
						norm_light.y = norm_light.y / len_l;
						norm_light.z = norm_light.z / len_l;
						normal.x = d.x / sphere2.r;
						dot = (normal.x * norm_light.x) + (normal.y * norm_light.y) + (normal.z * norm_light.z);
						if (dot < 0)
							dot = 0;
						mlx_pixel_put(mlx, win, i2, i,color_dot_amb(color2, dot, ambient));
					}
			else if ((act.x - rec.x) > -0.2 && (act.x - rec.x) < 0.2 && (act.y - rec.x)  > -0.2 && (act.y - rec.x)  < 0.2)
			{
				d.y = act.y - sphere2.vec.y;
				d.x = act.x - sphere2.vec.x;
    			mlx_pixel_put(mlx, win, i2, i, 0x00FF00);
			}
			else
				mlx_pixel_put(mlx, win, i2, i, color_dot_amb(color3, 0, 0));
			i2++;
		}
		i++;
	}


	mlx_loop(mlx);

    return (0);
}


int color_dot_union(t_vec3 color, double dot)
{
	t_vec3 new_color;

	new_color.x = color.x * dot;
	if (new_color.x > 255)
		new_color.x = 255;
	new_color.y= color.y * dot;
	if (new_color.y > 255)
		new_color.y = 255;
	new_color.z = color.z * dot;
	if (new_color.z > 255)
		new_color.z = 255;
	return ((int)new_color.x << 16 | (int)new_color.y << 8 | (int)new_color.z);
}

int color_dot_amb(t_vec3 color, double dot, double ambient)
{
	t_vec3 new_color;

	new_color.x = (dot + ambient) * color.x;
	// if (new_color.x > 255)
	// 	new_color.x = 255;
	new_color.y= (dot + ambient) * color.y;
	// if (new_color.y > 255)
	// 	new_color.y = 255;
	new_color.z = (dot + ambient) * color.z;
	// if (new_color.z > 255)
	// 	new_color.z = 255;
	while (new_color.x > 255 || new_color.z > 255 || new_color.y > 255)
	{
		if (new_color.x > 255)
		{
			new_color.y += ((int)new_color.x % 255) /2;
			new_color.z += ((int)new_color.x % 255) /2;
			new_color.x = 255;
		}
		if (new_color.y > 255)
		{
			new_color.z += ((int)new_color.y % 255) /2;
			new_color.x += ((int)new_color.y % 255) /2;
			new_color.y = 255;
		}
		if (new_color.z > 255)
		{
			new_color.y += ((int)new_color.z % 255) /2;
			new_color.x += ((int)new_color.z % 255) /2;
			new_color.z = 255;
		}
	}
	return ((int)new_color.x << 16 | (int)new_color.y << 8 | (int)new_color.z);
}
