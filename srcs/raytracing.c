#include "../includes/miniRT.h"

float	compute_lighting(t_vector *point, t_vector *normal, t_lstobjects *lights)
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
{
	int		ret_color;
	int		type;
	int		r;
	int		g;
	int		b;
	float		t_temp;
	float		closest_t;
	void		*closest_object;
	t_vector	*point;
	t_vector	*normal;
	t_vector	*color;
	t_vector	*new_color;
	
	closest_object = NULL;
	closest_t = -1;
	type = -1;
	while (objects)
	{
		if (objects->type == TYPE_SPHERE)
			t_temp = intersect_sphere(origin, direction, objects->object);
		if (t_temp > t_min_max[0] && (t_temp <  t_min_max[1] || t_min_max[1] == -1) && (t_temp < closest_t || closest_t == -1))
		{
			type = objects->type;
			closest_t = t_temp;
			closest_objet = objects->object;
		}
		objects = objects->next;
	}
	if (!closest_object)
		return (BACKGROUND_COLOR);
	point = add_vector(origin, *(scale_vector(closest_t, direction)));
	normal = sub_vector(*point, *(((t_sphere *)closest_object)->center));
	normal = scale_vector(1 / lenght_vector(*normal), *normal);
	if (type == TYPE_SPHERE)
	{
		color = color_to_rgb((t_sphere *)closest_object->color);
		new_color = scale_vector(compute_lighting(point, normal, lights), *color);
		free(color);
		if (new_color->x > 255)
			r = 255;
		else if (new_color->x < 0)
			r = 0;
		else
			r = new_color->x;
		if (new_color->y > 255)
			g = 255;
		else if (new_color->y < 0)
			g = 0;
		else
			g = new_color->y;
		if (new_color->z > 255)
			b = 255;
		else if (new_color->z < 0)
			b = 0;
		else
			b = new_color->z;
		set_vector(new_color, r, g, b);
		ret_color - rgb_to_color(new_color);
		free(new_color);
		return (ret_color);	
	}
	return (BACKGROUND_COLOR);	
}
