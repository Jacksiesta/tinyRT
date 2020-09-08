#include "../includes/miniRT.h"

/*
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
			// REFLECTION MATH 
			//l_vector->reflection = 0.7;
			if (l_vector->reflection != -1)
			{
				temp = scale_vector(2.0 * dot_vector(*l_vector->normal, *vec_l), *l_vector->normal);
				vec_r = sub_vector(*temp, *vec_l);
				free(temp);
				r_dot_v = dot_vector(*vec_r, *l_vector->view);
				if (r_dot_v > 0)
					intensity += light->intensity * pow(r_dot_v / (len_vector(*vec_r) * length_v), l_vector->reflection);
				free(vec_r);
			}	
			if (light->type == TYPE_POINT)
				free(vec_l);
		}
		lights = lights->next;
	}
	return (intensity);	
}*/

/*
int	calculate_new_color(t_lstobject *object, t_lstobject *lights, t_light_vector *l_vector)
{
	int		ret_color;
	t_vector	*normal;
	void		*obj;
	t_vector	*color;
	t_vector	*new_color;

	obj = object->object;
	if (object->type == TYPE_SPHERE)
		normal = sub_vector(*l_vector->point, *(((t_sphere *)obj)->center)); // get to center with dir of point
	else if (object->type == TYPE_PLAN)
		normal = sub_vector(*l_vector->point, *(((t_plan *)obj)->point));
	else if (object->type == TYPE_SQUARE)
		normal = sub_vector(*l_vector->point, *(((t_square *)obj)->center));
	else if (object->type == TYPE_TRIANGLE)
		normal = sub_vector(*l_vector->point, *(((t_triangle *)obj)->a)); // ->a ??
	else if (object->type == TYPE_CYLINDER)
		normal = sub_vector(*l_vector->point, *(((t_cylinder *)obj)->center));
	l_vector->normal = scale_vector(1 / len_vector(*normal), *normal); // scale from center
	free(normal);
	if (object->type == TYPE_SPHERE)
	{
		l_vector->reflection = ((t_sphere *)obj)->reflection;
		color = color_to_rgb(((t_sphere *)obj)->color);
		new_color = scale_vector(compute_lighting(l_vector, lights), *color);
		free(l_vector->normal);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	else if (object->type == TYPE_PLAN)
	{
		l_vector->reflection = ((t_plan *)obj)->reflection;
		//l_vector->reflection = 0.01;
		//printf("reflection plane is %f\n", l_vector->reflection);
		color = color_to_rgb(((t_plan *)obj)->color);		
		new_color = scale_vector(compute_lighting(l_vector, lights), *color);
		free(l_vector->normal);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	else if (object->type == TYPE_SQUARE)
	{
		l_vector->reflection = ((t_square *)obj)->reflection;
		//l_vector->reflection = 0.01;
		color = color_to_rgb(((t_square *)obj)->color);
		new_color = scale_vector(compute_lighting(l_vector, lights), *color);
		free(l_vector->normal);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	else if (object->type == TYPE_TRIANGLE)
	{
		l_vector->reflection = ((t_triangle *)obj)->reflection;
		l_vector->reflection = 0.2;
		//printf("reflection is %f\n", l_vector->reflection);
		color = color_to_rgb(((t_triangle *)obj)->color);
		new_color = scale_vector(compute_lighting(l_vector, lights), *color);
		free(l_vector->normal);
		free(color);
		rearrange_rgb(new_color);
		ret_color = rgb_to_color(new_color);
		free(new_color);
		return (ret_color);
	}
	else if (object->type == TYPE_CYLINDER)
	{
		l_vector->reflection = ((t_cylinder *)obj)->reflection;
		color = color_to_rgb(((t_cylinder *)obj)->color);
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
}*/


t_vector	*reflect_ray(t_vector v1, t_vector v2)
{
	t_vector	*v_temp;
	t_vector	*new;

	v_temp = scale_vector(2 * dot_vector(v1, v2), v2);
	new = sub_vector(*v_temp, v1);
	free(v_temp);
	return (new);
}

int	color_with_reflect(t_lstobject *closest_object, t_scene *scene, t_light_vector *l_vectors, int color)
{
	t_vector	*temp;
	t_vector	*temp2;
	t_vector	*reflect_color;

	temp = reflect_ray(*(l_vectors->view), *(l_vectors->normal));
	temp2 = color_to_rgb(color);
	((t_camera *)scene->camera->object)->origin = l_vectors->point;
	scene->depth--;
	color = trace_ray(*temp, scene);
	free(temp);
	if (closest_object->type == TYPE_SPHERE)
		temp = scale_vector(1 - ((t_sphere *)closest_object)->reflection, *temp2);
	else if (closest_object->type == TYPE_PLAN)
		temp = scale_vector(1 - ((t_plan *)closest_object)->reflection, *temp2);
	else if (closest_object->type == TYPE_SQUARE)
		temp = scale_vector(1 - ((t_square *)closest_object)->reflection, *temp2);
	else if (closest_object->type == TYPE_TRIANGLE)
		temp = scale_vector(1 - ((t_triangle *)closest_object)->reflection, *temp2);
	else if (closest_object->type == TYPE_CYLINDER)
		temp = scale_vector(1 - ((t_cylinder *)closest_object)->reflection, *temp2);
	free(reflect_color);
	reflect_color = add_vector(*temp, *temp2);
	free(temp);
	free(temp2);
	rearrange_rgb(reflect_color);
	color = rgb_to_color(reflect_color);
	free(reflect_color);
	return (color);
}

int	calculate_new_color(t_lstobject *objects, t_lstobject *lights, t_light_vector *l_vectors, t_scene *scene)
{
	int			ret_color;
	void		*obj;
	t_vector	*new_color;
	t_vector	*temp;

	temp = NULL;
	obj = objects->object;
	if (objects->type == TYPE_SPHERE) // calculate norm
		temp = sub_vector(*l_vectors->point, *(((t_sphere *)obj)->center)); // get to center with dir of point
	else if (objects->type == TYPE_PLAN)
		temp = sub_vector(*l_vectors->point, *(((t_plan *)obj)->point));
	else if (objects->type == TYPE_SQUARE)
		temp = sub_vector(*l_vectors->point, *(((t_square *)obj)->center));
	else if (objects->type == TYPE_TRIANGLE)
		temp = sub_vector(*l_vectors->point, *(((t_triangle *)obj)->a));
	else if (objects->type == TYPE_CYLINDER)
		temp = sub_vector(*l_vectors->point, *(((t_cylinder *)obj)->center));
	l_vectors->normal = scale_vector(1 / len_vector(*temp), *temp); // scale from center
	free(temp);
	if (objects->type == TYPE_SPHERE)
	{
		l_vectors->shiny = ((t_sphere *)obj)->shiny;
		temp = color_to_rgb(((t_sphere *)obj)->color);
	}
	else if (objects->type == TYPE_PLAN)
	{
		l_vectors->shiny = ((t_plan *)obj)->shiny;
		temp = color_to_rgb(((t_plan *)obj)->color);
	}
	else if (objects->type == TYPE_SQUARE)
	{
		l_vectors->shiny = ((t_square *)obj)->shiny;
		temp = color_to_rgb(((t_square *)obj)->color);
	}
	else if (objects->type == TYPE_TRIANGLE)
	{
		l_vectors->shiny = ((t_triangle *)obj)->shiny;
		temp = color_to_rgb(((t_triangle *)obj)->color);
	}
	else if (objects->type == TYPE_CYLINDER)
	{
		l_vectors->shiny = ((t_cylinder *)obj)->shiny;
		temp = color_to_rgb(((t_cylinder *)obj)->color);
	}
	new_color = scale_vector(compute_lighting(l_vectors, lights, scene), *temp);
	free(temp);
	rearrange_rgb(new_color);
	ret_color = rgb_to_color(new_color);
	free(new_color);
	return (ret_color);
}

int	set_l_vec_and_calc(t_lstobject *closest_object, t_vector direction, float closest_t, t_scene *scene)
{
	int				final_color;
	t_light_vector	*l_vectors;
	t_vector		*temp;

	final_color = 0;
	if (!(l_vectors = malloc(sizeof(t_light_vector))))
		return (-1);
	temp = scale_vector(closest_t, direction);
	l_vectors->point = add_vector(*((t_camera *)scene->camera->object)->origin, *(temp));
	free(temp);
	l_vectors->view = scale_vector(-1, direction);
	final_color = calculate_new_color(closest_object, scene->lights, l_vectors, scene);
	if (closest_object->type == TYPE_SPHERE && (((t_sphere *)closest_object->object)->reflection > 0 && scene->depth > 0))
		final_color = color_with_reflect(closest_object, scene, l_vectors, final_color);
	else if (closest_object->type == TYPE_PLAN && (((t_plan *)closest_object->object)->reflection > 0 && scene->depth > 0))
		final_color = color_with_reflect(closest_object, scene, l_vectors, final_color);
	else if (closest_object->type == TYPE_SQUARE && (((t_square *)closest_object->object)->reflection > 0 && scene->depth > 0))
		final_color = color_with_reflect(closest_object, scene, l_vectors, final_color);
	else if (closest_object->type == TYPE_TRIANGLE && (((t_triangle *)closest_object->object)->reflection > 0 && scene->depth > 0))
		final_color = color_with_reflect(closest_object, scene, l_vectors, final_color);
	else if (closest_object->type == TYPE_CYLINDER && (((t_cylinder *)closest_object->object)->reflection > 0 && scene->depth > 0))
		final_color = color_with_reflect(closest_object, scene, l_vectors, final_color);
	free(l_vectors->point);
	free(l_vectors->normal);
	free(l_vectors->view);
	free(l_vectors);
	return (final_color);
}

float	closest_inters(t_vector origin, t_vector direction, t_scene *scene, t_lstobject **closest_object)
{
	float		t_temp;
	float		closest_t;
	t_lstobject	*objects;

	*closest_object = NULL;
	closest_t = -1;
	objects = scene->objects;
	printf("COUCOU\n");
	while (objects)
	{
		if (objects->type == TYPE_SPHERE)
			t_temp = intersect_sphere(origin, direction, objects->object);
		if (objects->type == TYPE_PLAN)
			t_temp = intersect_plan(origin, direction, objects->object);
		if (objects->type == TYPE_SQUARE)
			t_temp = intersect_square(origin, direction, objects->object);
		if (objects->type == TYPE_TRIANGLE)
			t_temp = intersect_triangle(origin, direction, objects->object);
		if (objects->type == TYPE_CYLINDER)
			t_temp = intersect_cyl(origin, direction, objects->object);
		// t_min < t_temp < t_max
		if (t_temp > scene->t_min && (t_temp < scene->t_max || scene->t_max == -1) && (t_temp < closest_t || closest_t == -1))
		{
			closest_t = t_temp;
			*closest_object = objects;
		}
		scene->t_max = -1;
		objects = objects->next;
	}
	return (closest_t);

}

int	trace_ray(t_vector direction, t_scene *scene)
{
	float		closest_t;
	t_lstobject	*closest_object;
	int		color;

	closest_t = closest_inters(*(((t_camera *)scene->camera->object)->origin), direction, scene, &closest_object);
	if (!closest_object)
		return (scene->background_color);
	color = set_l_vec_and_calc(closest_object, direction, closest_t, scene);
	return (color);
}

/*
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
		if (objects->type == TYPE_PLAN)
			t_temp = intersect_plan(*scene->origin, direction, objects->object);
		if (objects->type == TYPE_SQUARE)
			t_temp = intersect_square(*scene->origin, direction, objects->object);
		if (objects->type == TYPE_TRIANGLE)
			t_temp = intersect_triangle(*scene->origin, direction, objects->object);	
		if (objects->type == TYPE_CYLINDER)
			t_temp = intersect_cyl(*scene->origin, direction, objects->object);	
		// t_min < t_temp < t_max
		if (t_temp > scene->t_min && (t_temp < scene->t_max || scene->t_max == -1) && (t_temp < closest_t || closest_t == -1))
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
	l_vector->point = add_vector(*scene->origin, *(temp));
	free(temp);
	l_vector->view = scale_vector(-1, direction);
	final_color = calculate_new_color(closest_object, scene->lights, l_vector);
	free(l_vector->point);
	free(l_vector->view);
	free(l_vector);
	return (final_color);
}*/
