#include "../includes/miniRT.h"

float	compute_lightning(t_vector *point, t_vector *normal, t_lstobjects *lights)
{
	float		intensity;
	t_light		*light;
	t_vector	*vec_l;
	float		n_dot_l;
	float		length_n;

	length_n = length_vector(*normal);
	intensity = 0;
	while (lights)
	{
		light = ((t_light *)lights->object);
		if (light->type == TYPE_AMBIENT)
			intensity += light->intensity;
		else
		{
			if (light->type == TYPE_POINT)
				vec_l = sub_vector(*light->vector, *point);
			else if (light->type == TYPE_DIRECTIONAL)
				vec_l = light->vector;
			n_dot_l = dot_vector(*normal, *vec_l);
			if (n_dot_l > 0)
				intensity += light->intensity * n_dot_l / lenght->vector(*vec_l);	
		}
		lights = lights->next;
	}
	return (intensity);	
}

float	intersect_sphere(t_vector obs, t_vector direction, t_sphere *object)
{
	t_vector	*difference;
	float		discr;
	float		k[3];
	float		r[2];
	
	difference = new_vector(obs.x - object->center->x, obs.y - object->center->y, obs.z - object->center->z);
	k[0] = dot_vector(direction, direction);
	k[1] = 2 * dot_vector(*difference, direction);
	k[2] = dot_vector(*difference, *difference) - (object->radius * object->radius);
	discr = k[1] * k[1] - 4 * k[0] * k[2]; // B * B - 4 * A * C
	free(difference);
	if (discr < 0) // no intersection
		return (0);
	r[0] = (-k[1] + ft_squrt_bin(discr)) / (2 * k[0]);
	r[1] = (-k[1] - ft_squrt_bin(discr)) / (2 * k[0]);
	if (r[0] < r[1])
		return (r[0]);
	return (r[1]);
}

int	trace_ray(t_vector origin, t_vector direction, t_lstobjects *objects, float t_min_max[2], t_lstobject *lights)

