#include "../includes/miniRT.h"
//#include "miniRT.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

float	ft_squrt_bin(float x)
{
	int	i;
	float j;

	j = x;
	i = (1 << 29) + (i >> 1) - (1 << 22);
	j = 0.5f * (j + x/j);
	j = 0.5f * (j + x/j);
	return (j);
}

int		main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_canvas		*viewport;
	t_vector		*obs;
	t_vector		*direction;
	t_lstobject		*lstobj;
	t_lstobject		*lstlight;
	int			color;
	int			x;
	int			y;
	t_scene			*scene;

	/**	WINDOW **/
	mlx_ptr = mlx_init();
	viewport = new_canvas(700, 700, 4);
	win_ptr = mlx_new_window(mlx_ptr, viewport->width, viewport->height, "miniRT");
	/** SPHERES & O **/
	obs = new_vector(0, 0, -5);
	lstobj = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xff0074)); //pink
	set_vector(((t_sphere *)lstobj->object)->center, 0, -1.5, 3);
	set_reflection((t_sphere *)lstobj->object, 0.4);
	lstobj->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0x00cccc)); //blue
	set_vector(((t_sphere *)((t_lstobject *)lstobj->next)->object)->center, 2, 0, 7);
	set_reflection(((t_sphere *)((t_lstobject *)lstobj->next)->object), 0.9);
	((t_lstobject *)lstobj->next)->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xf1c40f)); //yellow
	set_vector(((t_sphere *)((t_lstobject *)((t_lstobject *)lstobj->next)->next)->object)->center, -2, 2, 4);
	set_reflection(((t_sphere *)((t_lstobject *)((t_lstobject *)lstobj->next)->next)->object), 0.5);
	/** PLANE **/
	((t_lstobject *)((t_lstobject *)lstobj->next)->next)->next = new_obj(TYPE_PLAN, new_plan(new_vector(0, -1.5, 3), new_vector(1, -3, 0), 0xd10f42));
	/** LIGHTS **/
	lstlight = new_obj(TYPE_LIGHT, new_default_light(TYPE_AMBIENT, 0.2));
	lstlight->next = (t_lstobject *)new_obj(TYPE_LIGHT, new_default_light(TYPE_POINT, 0.5));
	set_vector(((t_light *)((t_lstobject *)lstlight->next)->object)->vector, -3, 1, -1);
	((t_lstobject *)lstlight->next)->next = new_obj(TYPE_LIGHT, new_default_light(TYPE_DIRECTIONAL, 0.7));
	set_vector(((t_light *)((t_lstobject *)((t_lstobject *)lstlight->next)->next)->object)->vector, 0, -15, -5);
	scene = new_scene(obs, lstobj, lstlight, 0x0); // fill info in scene
	/** RENDERING **/
	x = -(viewport->width/2) + 1;
	while ((x + (viewport->width/2) <= viewport->width))
	{
		y = -(viewport->height/2);
		while (y < viewport->height/2)
		{
			//printf("reflection sphere 1 is %f\n", ((t_sphere *)lstobj->object)->reflection);
			direction = new_vector(x / viewport->width, y / viewport->height, 1);
			//color = trace_ray(*obs, *direction, lstobj, lstlight);
			color = trace_ray(*direction, scene);
			if (color != BACKGROUND_COLOR)
				mlx_pixel_put(mlx_ptr, win_ptr, (int)(x + (viewport->width/2)), (int)(y + (viewport->height/2)), (int)color);
			free(direction);
			y++;
		}
		x++;
	}
	mlx_loop(mlx_ptr);
}
