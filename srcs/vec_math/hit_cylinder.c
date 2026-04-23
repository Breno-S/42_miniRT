/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:13:13 by brensant          #+#    #+#             */
/*   Updated: 2026/04/23 17:59:49 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "ray.h"
#include "shapes.h"
#include "vec_math.h"

#include <math.h>
#include <float.h>

static float	get_visible_scalar(t_hit *hit, t_ray *ray, float t0, float t1)
{
	float	y_close;
	float	y_far;
	float	half_height;
	// t_vec3	hit_close;
	// t_vec3	hit_far;

	half_height = hit->obj->cylinder.height / 2.0;
	y_close = ray->orig.y + ray->dir.y * t0;
	// hit_close = ray_at(ray, t0);
	y_far = ray->orig.y + ray->dir.y * t1;
	//hit_far = ray_at(ray, t1);

	if (t0 > FLT_EPSILON && (y_close < (hit->obj->pos.y + half_height)
		&& y_close > (hit->obj->pos.y - half_height)))
		return (t0);
	if (t1 > FLT_EPSILON && (y_far < (hit->obj->pos.y + half_height)
		&& y_far > (hit->obj->pos.y - half_height)))
		return (t1);
	return (-1);
}

// static float    get_valid_t(t_obj *obj, t_ray *ray, float t0, float t1)
// {
//     float y0;
//     float y1;
//     float half_h = obj->cylinder.height / 2.0;

//     // 1. Testa o t mais próximo (frente)
//     if (t0 > FLT_EPSILON)
//     {
//         y0 = ray->orig.y + ray->dir.y * t0;
//         if (y0 >= obj->pos.y - half_h && y0 <= obj->pos.y + half_h)
//             return (t0); // Retorna o SCALAR t0, não a altura y0
//     }

//     // 2. Se o t0 falhou (altura ou distância), testa o t1 (trás/interior)
//     if (t1 > FLT_EPSILON)
//     {
//         y1 = ray->orig.y + ray->dir.y * t1;
//         if (y1 >= obj->pos.y - half_h && y1 <= obj->pos.y + half_h)
//             return (t1); // Retorna o SCALAR t1
//     }

//     return (-1.0);
// }

// static void	set_hit(t_hit *hit, t_ray *ray, t_vec4 *coeff)
// {
// 	float	closest_hit_scalar;
// 	float	farthest_hit_scalar;
// 	float	t;

// 	if (coeff->w)
// 	{
// 		*hit = hit_miss();
// 		return ;
// 	}
// 	closest_hit_scalar = (-coeff->y - coeff->w) / (2.0 * coeff->x);
// 	farthest_hit_scalar = (-coeff->y + coeff->w) / 2.0 * coeff->x;
// 	// hit->hit_in = ray_at(ray, closest_hit_scalar);
// 	// hit->hit_out = ray_at(ray, farthest_hit_scalar);
// 	t = get_valid_t(hit->obj, ray, closest_hit_scalar, farthest_hit_scalar);
// 	if (t >= FLT_EPSILON)
// 	{
// 		hit->did_hit = true;
// 		hit->distance = t;
// 		hit->point = ray_at(ray, t);
// 		hit->normal = vec3_normalize((t_vec3){hit->point.x
// 				- hit->obj->pos.x, 0, hit->point.z - hit->obj->pos.z});
// 		if (vec3_dot(ray->dir, hit->normal) > FLT_EPSILON)
// 			hit->normal = vec3_negate(hit->normal);
// 	}
// 	else
// 		*hit = hit_miss();
// }

static void    set_hit(t_hit *hit, t_ray *ray, t_vec4 *coeff)
{
    float    t0;
    float    t1;
    float    t;

    // Correção dos parênteses no divisor (2.0 * a)
    t0 = (-coeff->y - coeff->w) / (2.0 * coeff->x);
    t1 = (-coeff->y + coeff->w) / (2.0 * coeff->x);

    t = get_visible_scalar(hit, ray, t0, t1);

    if (t > FLT_EPSILON)
    {
        hit->did_hit = true;
        hit->distance = t;
        hit->point = ray_at(ray, t);

        // Normal lateral (ignora Y)
        hit->normal = vec3_normalize((t_vec3){
            hit->point.x - hit->obj->pos.x,
            0,
            hit->point.z - hit->obj->pos.z
        });

        // Inversão da normal para o interior
        if (vec3_dot(ray->dir, hit->normal) > 0)
            hit->normal = vec3_negate(hit->normal);
    }
    else
        hit->did_hit = false;
}

/**
 * `coeff.x = a;
 * `coeff.y = b;
 * `coeff.z = c;
 * `coeff.w = sqrt(discriminant);
 *
 * `a = 1` porque `a = dot(ray->dir, ray->dir)` e `|| ray->dir || = 1`
 */
t_hit	hit_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_hit	hit;
	t_vec3	oc;
	t_vec4	coeff;

	oc = vec3_sub(ray->orig, cylinder->pos);
	coeff.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	coeff.y = 2.0 * (ray->dir.x * oc.x + ray->dir.z * oc.z);
	coeff.z = oc.x * oc.x + oc.z * oc.z
		- cylinder->cylinder.radius * cylinder->cylinder.radius;
	coeff.w = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (coeff.w < 0)
		return (hit_miss());
	coeff.w = sqrt(coeff.w);
	hit.obj = cylinder;
	set_hit(&hit, ray, &coeff);
	return (hit);
}
