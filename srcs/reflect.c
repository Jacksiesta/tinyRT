#include "../includes/miniRT.h"

t_vector	*reflect_ray(t_vector v1, t_vector v2)
{
	t_vector *v_temp;
	t_vector *new;

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
