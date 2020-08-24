#include "../includes/miniRT.h"

float	compute_lighting(t_light_vector *l_vector, t_lstobject *lights)
{
	float		intensity;
	t_light		*light;
	t_vector	*vec_l;
	t_vector	*vec_r;
	float		n_dot_l;
	float		r_dot_v;
	float		length_n;
	float		length_v;
	t_vector	*temp;

	length_v = len_vector(*l_vector->view);
	length_n = len_vector(*l_vector->normal);
	intensity = 0;
	while (lights) //check all light sources
	{
		light = ((t_light *)lights->object);
		if (light->type == TYPE_AMBIENT)
			intensity += light->intensity;
		else
		{
			if (light->type == TYPE_POINT)
				vec_l = sub_vector(*light->vector, *l_vector->point);
			else if (light->type == TYPE_DIRECTIONAL)
				vec_l = light->vector;
			n_dot_l = dot_vector(*l_vector->normal, *vec_l);
			if (n_dot_l > 0) // ray outside 
				intensity += light->intensity * n_dot_l / len_vector(*vec_l);
			/* REFLECTION MATH */
			if (l_vector->reflection != -1)
			{
				temp = scale_vector(2.0 * dot_vector(*l_vector->normal, *vec_l), *l_vector->normal);
				vec_r = sub_vector(*temp, *vec_l);
				free(temp);
				r_dot_v = dot_vector(*vec_r, *l_vector->view);
				if (r_dot_v > 0)
				{
					intensity += light->intensity * pow(r_dot_v / (len_vector(*vec_r) * length_v), l_vector->reflection);
				}
				free(vec_r);
			}	
			if (light->type == TYPE_POINT)
				free(vec_l);
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

int	calculate_new_color(t_lstobject *object, t_lstobject *lights, t_light_vector *l_vector)
{
	int		ret_color;
	t_vector	*normal;
	void		*obj;
	t_vector	*color;
	t_vector	*new_color;
	t_vector	*point;

	obj = object->object;
	printf("rhello\n");
	printf("center x %f \n", ((t_sphere *)obj)->center->x);
	printf("center y %f \n", ((t_sphere *)obj)->center->y);
	printf("center z %f \n", ((t_sphere *)obj)->center->z);
	printf("l vector point x is %f\n", l_vector->point->x);
	printf("l vector point y is %f\n", l_vector->point->y);
	printf("l vector point z is %f\n", l_vector->point->z);
	point = l_vector->point;
	printf(" point x is %f\n", point->x);
	normal = sub_vector(*point, *(((t_sphere *)object)->center)); // get to center with dir of point
	printf("i'm here\n");
	l_vector->normal = scale_vector(1 / len_vector(*normal), *normal); // scale from center
	free(normal);
	if (object->type == TYPE_SPHERE)
	{
		l_vector->reflection = ((t_sphere *)object)->reflection;
		color = color_to_rgb(((t_sphere *)object)->color);
		new_color = scale_vector(compute_lighting(l_vector, lights), *color);
		free(l_vector->normal);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	free(l_vector->normal);
	return (BACKGROUND_COLOR);
}

// returns correct color at given ray 
int	trace_ray(t_vector direction, t_scene *scene)
{
	float		t_temp;
	float		closest_t;
	t_lstobject	*closest_object;
	t_light_vector	*l_vector;
	t_lstobject	*objects;
	t_vector	*temp;
	int		final_color;
	
	closest_object = NULL;
	closest_t = -1;
	objects = scene->objects;
	while (objects) // check all objects present to find closest_object
	{
		if (objects->type == TYPE_SPHERE)
			t_temp = intersect_sphere(*scene->origin, direction, objects->object);
		// t_min < t_temp < t_max
		if (t_temp > scene->t_min && (t_temp <  scene->t_max || scene->t_max == -1) && (t_temp < closest_t || closest_t == -1))
		{
			closest_t = t_temp;
			closest_object = objects;
		}
		objects = objects->next;
	}
	if (!closest_object)
		return (scene->background_color);
	l_vector = malloc(sizeof(t_light_vector));
	temp = scale_vector(closest_t, direction);
	printf("scene origin is %f\n", scene->origin->z);
	l_vector->point = add_vector(*scene->origin, *(temp));
	free(temp);
	l_vector->view = scale_vector(-1, direction);
	printf("direction %f %f %f \n", direction.x, direction.y, direction.z);
	printf("pont is %f %f %f\n", l_vector->point->x, l_vector->point->y, l_vector->point->z);
	printf("view is %f %f %f\n", l_vector->view->x, l_vector->view->y, l_vector->view->z);
	final_color = calculate_new_color(closest_object, scene->lights, l_vector);
	printf("yes\n");
	free(l_vector->point);
	free(l_vector->view);
	free(l_vector);
	printf("%i\n", final_color);
	return (final_color);
}
