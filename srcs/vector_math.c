#include "../includes/miniRT.h"

float			len_vector(t_vector v)
{
	return (ft_squrt_bin(dot_vector(v, v)));
}

float			dot_vector(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float			distance_points(t_vector a, t_vector b)
{
	float dist;
	
	dist = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z);
	return (sqrt(dist));	
}

t_vector		*add_vector(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector		*sub_vector(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector		*scale_vector(float c, t_vector v)
{
	return (new_vector((c * v.x), (c * v.y), (c * v.z)));
}

t_vector		*cross_product(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x * v2.y - v1.y * v2.x, v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z));	
}

