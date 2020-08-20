#include "../includes/miniRT.h"

float	compute_lighting(t_vector *point, t_vector *normal, t_lstobject *lights)
{
	float		intensity;
	t_light		*light;
	t_vector	*vec_l;
	float		n_dot_l;
	float		length_n;

	length_n = len_vector(*normal);
	intensity = 0;
	while (lights) //check all light sources
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
			if (n_dot_l > 0) // ray outside 
				intensity += light->intensity * n_dot_l / len_vector(*vec_l);	
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

int	calculate_new_color(int type, t_lstobject *object, t_lstobject *lights, t_vector *point)
{
	int		ret_color;
	t_vector	*normal;
	t_vector	*color;
	t_vector	*new_color;

	normal = sub_vector(*point, *(((t_sphere *)object)->center)); //get to center with dir of point
	normal = scale_vector(1 / len_vector(*normal), *normal); //scale from center
	if (type == TYPE_SPHERE)
	{
		color = color_to_rgb(((t_sphere *)object)->color);
		new_color = scale_vector(compute_lighting(point, normal, lights), *color);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	return (BACKGROUND_COLOR);
}

// returns correct color at given ray 
int	trace_ray(t_vector origin, t_vector direction, t_lstobject *objects, t_lstobject *lights)
{
	float		t_temp;
	float		closest_t;
	t_lstobject	*closest_object;
	t_vector	*point;
	float		t_min_max[2];
	
	t_min_max[0] = 1;
	t_min_max[1] = -1;
	closest_object = NULL;
	closest_t = -1;
	while (objects) // check all objects present to find closest_object
	{
		if (objects->type == TYPE_SPHERE)
			t_temp = intersect_sphere(origin, direction, objects->object);
		// t_min < t_temp < t_max
		if (t_temp > t_min_max[0] && (t_temp <  t_min_max[1] || t_min_max[1] == -1) && (t_temp < closest_t || closest_t == -1))
		{
			closest_t = t_temp;
			closest_object = objects;
		}
		objects = objects->next;
	}
	if (!closest_object)
		return (BACKGROUND_COLOR);
	point = add_vector(origin, *(scale_vector(closest_t, direction))); //hit point on object
	return (calculate_new_color(closest_object->type, closest_object->object, lights, point));
}
