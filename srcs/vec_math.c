#include "vec_math.h"

t_vec4	vec3_negate(t_vec4 v)
{
	return ((t_vec4){-v.x, -v.y, -v.z, -v.w});
}

t_vec4	vec3_scale(t_vec4 v, float scalar)
{
	return ((t_vec4){scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w});
}

t_vec4	vec3_add(t_vec4 u, t_vec4 v)
{
	return ((t_vec4){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec4	vec3_sub(t_vec4 u, t_vec4 v)
{
	return ((t_vec4){u.x - v.x, u.y - v.y, u.z - v.z});
}

float	vec3_dot(t_vec4 u, t_vec4 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec4	vec3_cross(t_vec4 u, t_vec4 v)
{
	return ((t_vec4){u.y * v.z - v.y * u.z, u.z * v.x - v.z * u.x,
		u.x * v.y - v.x * u.y});
}

t_vec4	vec3_transform(t_vec4 v, t_matrix m)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = v.x * m.r0[0] + v.y * m.r0[1] + v.z * m.r0[2] + 1 * m.r0[3];
	y = v.x * m.r1[0] + v.y * m.r1[1] + v.z * m.r1[2] + 1 * m.r1[3];
	z = v.x * m.r2[0] + v.y * m.r2[1] + v.z * m.r2[2] + 1 * m.r2[3];
	w = v.x * m.r3[0] + v.y * m.r3[1] + v.z * m.r3[2] + 1 * m.r3[3];
	return ((t_vec4){x, y, z, w});
}
