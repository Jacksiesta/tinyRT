float	calcul_shiny(t_light_vector *l_vectors, t_light *light, float lenght_v, t_vector *vec_l)
{
	float		r_dot_v;
	t_vector	*vec_r;
	t_vector	*temp;
	float		intensity;

	intensity = 0;
	temp = scale_vector(2 * dot_vector(*l_vectors->normal, *vec_l), *l_vectors->normal);
	vec_r = sub_vector(*temp, *vec_l);
	free(temp);
	r_dot_v = dot_vector(*vec_r, *l_vectors->view);
	if (r_dot_v > 0)
		intensity += light->intensity * pow(r_dot_v / (len_vector(*vec_r) * lenght_v), l_vectors->shiny);
	free(vec_r);
	return (intensity);
}

t_vector	*type_light(t_light_vector *l_vectors, t_light *light, t_scene *scene)
{
	t_vector	*vec_l;

	vec_l = NULL;
	if (light->type == TYPE_POINT)
	{
		vec_l = sub_vector(*light_vector, *l_vectors->point);
		scene->t_max = 1;
	}
	else if (light->type == TYPE_DIRECTIONAL)
	{
		vec_l = light->vector;
		scene->t_max = -1;
	}
	scene->t_min = 0.001;
	return (vec_l);
}

float	compute_special_lights(t_light_vector *l_vectors, t_light *light, t_scene *scene)
{
	float		intensity;
	float		n_dot_l;
	float		lenght_v;
	float		test;
	t_vector	*vec_l;
	t_lstobject	*shadow_obj;

	intensity = 0;
	lenght_v = len_vector(*l_vectors->view);
	vec_l = type_light(l_vectors, light, scene);
	test = closest_inters(*l_vectors->point, *vec_l, scene, &shadow_obj);
	if (!shadow_obj) // not in shadow
	{
		n_dot_l = dot_vector(*l_vectors->normal, *vec_l);
		if (n_dot_l > 0)
			intensity += ((light->intensity * n_dot_l) / ((len_vector(*l_vectors->normal * len_vector(*vec_l)))));
		if (l_vectors->shiny != -10
			intensity += calcul_shiny(l_vectors, light, lenght_v, vec_l));
	}
	if (light->type == TYPE_POINT)
		free(vec_l);
	return (intensity);
}

float	compute_lighting(t_light_vector *l_vectors, t_lstobject *lights, t_scene *scene)
{
	float	intensity;
	t_light	*light;

	intensity = 0;
	while (lights) // pass over all light sources
	{
		light = ((t_light *)lights->object);
		if (light->type == TYPE_AMBIENT)
			intensity += light->intensity;
		else
			intensity += compute_special_lights(l_vectors, light, scene);
		lights = lights->next; // next light
	}
	return (intensity);
}
