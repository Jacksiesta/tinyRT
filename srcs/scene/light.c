#include "../../includes/light.h"

t_light		*new_default_light(int type, float intensity, int color)
{
	t_light		*light;

	light = malloc(sizeof(t_light));
	light->type = type;
	light->intensity = intensity;
	light->vector = new_vector(0, 0, 0);
	light->color = color;
	return (light);
}
