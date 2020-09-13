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

void	putimage(char *data, int bpp, int size_line, int x, int y, int color)
{
	int 	i;

	i = (x * (bpp / 8)) + (y * size_line);
	data[i] = color;
	data[++i] = color >> 8;
	data[++i] = color >> 16;
}

int main(int argc, char *argv[])
{

	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlx_img;
	int			fd;
	int			color;
	t_scene			*scene;
	t_vector		*angle;
	char			*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_vector		*direction;
	int			x;
	int			y;
	t_vector		*obs;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	scene = parsing(fd);
	if (scene->viewport->height < scene->viewport->width)
		scene->viewplane = new_canvas(scene->viewport->width/scene->viewport->height, 1, 1);
	else
		scene->viewplane = new_canvas(1, scene->viewport->height/scene->viewport->width, 1);
	mlx_ptr = mlx_init();
	mlx_img = mlx_new_image(mlx_ptr, scene->viewport->width, scene->viewport->height);
	win_ptr = mlx_new_window(mlx_ptr, scene->viewport->width, scene->viewport->height, "miniRT");

	angle = new_vector(((t_camera *)scene->camera->object)->rotation->x/1 * 180, ((t_camera *)scene->camera->object)->rotation->y/1 * 180, ((t_camera *)scene->camera->object)->rotation->z/1 * 180);
	x = -(scene->viewport->width/2);
	data = mlx_get_data_addr(mlx_img, &bpp, &size_line, &endian);
	obs = ((t_camera *)scene->camera->object)->origin;
	printf("viewplane : (%f, %f)\n", scene->viewplane->width, scene->viewplane->height);
	printf("viewport : (%f, %f)\n", scene->viewport->width, scene->viewport->height);
	printf("angle (%f, %f, %f)\n", angle->x, angle->y, angle->z);
	while ((x + (scene->viewport->width/2) <= scene->viewport->width))
	{
		//printf("ok\n");
		y = -(scene->viewport->height/2);
		while (y <= scene->viewport->height/2)
		{
			//printf("y : %d\n", y);
			direction = new_vector(x * (scene->viewplane->width / scene->viewport->width), y * (scene->viewplane->height / scene->viewport->height), 1);
			rot(direction, angle);
			//printf("direction (%f, %f, %f)\n", direction->x, direction->y, direction->z);
			color = trace_ray(*direction, scene);
			if (color != scene->background_color)
			{
				putimage(data, bpp, size_line, (int)((x + (scene->viewport->width/2))), (int)((-(y - (scene->viewport->height/2)))), color);
				//printf("ko\n");
				//mlx_pixel_put(mlx_ptr, win_ptr, (int)(x + (viewport->width/2)), (int)(-(y - (viewport->height/2))), (int)color);
			}
			free(direction);
			((t_camera *)scene->camera->object)->origin = obs;
			scene->depth = 3;
			y++;
		}
		x++;
	}
	//data = mlx_get_data_addr(mlx_img, &bpp, &size_line, &endian);
	//printf("data %s\n", data);
	//mlx_img = mlx_new_image(mlx_ptr, viewport->width, viewport->height);
	//mlx_ptr2 = mlx_init();
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_img, 0, 0);
	mlx_loop(mlx_ptr);
}















/*
int		main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_canvas		*viewport;
	t_vector		*obs;
	t_vector		*direction;
	t_lstobject		*lstobj;
	t_lstobject		*lstlight;
	t_camera		*camera;
	int			color;
	int			x;
	int			y;
	t_scene			*scene;
	t_vector		*rot;

	///WINDOW
	mlx_ptr = mlx_init();
	viewport = new_canvas(700, 700, 1);
	win_ptr = mlx_new_window(mlx_ptr, viewport->width, viewport->height, "miniRT");
	// SPHERES & O
	obs = new_vector(0, 0, -5);
	//rot = new_vector(0.001, 0.003, 0);
	//camera = new_camera(obs, rot, 10);
	lstobj = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xff0074)); //pink
	set_vector(((t_sphere *)lstobj->object)->center, 0, -1.5, 3);
	set_reflection((t_sphere *)lstobj->object, 0.4);
	lstobj->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0x00cccc)); //blue
	set_vector(((t_sphere *)((t_lstobject *)lstobj->next)->object)->center, 2, 0, 7);
	set_reflection(((t_sphere *)((t_lstobject *)lstobj->next)->object), 0.9);
	//((t_lstobject *)lstobj->next)->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xf1c40f)); //yellow
	//set_vector(((t_sphere *)((t_lstobject *)((t_lstobject *)lstobj->next)->next)->object)->center, -2, 2, 4);
	//set_reflection(((t_sphere *)((t_lstobject *)((t_lstobject *)lstobj->next)->next)->object), 0.5);
	// PLANE //
	//lstobj->next = new_obj(TYPE_PLAN, new_plan(new_vector(0, -1.5, 3), new_vector(0, 0, -0.5), 0xd10f42));
	//((t_lstobject *)((t_lstobject *)lstobj->next)->next)->next = new_obj(TYPE_PLAN, new_plan(new_vector(0, -1.5, 3), new_vector(0.2, -0.8, 0), 0xd10f42));
	// SQUARE //
	//lstobj->next = new_obj(TYPE_SQUARE, new_square(new_vector(0, -0.5, 2), new_vector(0.1, 0.1, 0.1), 3, 0x5bc898));
	//(((t_lstobject *)((t_lstobject *)(t_lstobject *)lstobj->next))->next = new_obj(TYPE_SQUARE, new_square(new_vector(2, 0, 7), new_vector(0.1, 0.1, 0.1), 5, 0xfbd0c1)));
	// TRIANGLE //
	//((t_lstobject *)lstobj->next)->next = new_obj(TYPE_TRIANGLE, new_triangle(new_vector(-2, 0, 1), new_vector(2, 0, 2), new_vector(0, 4, 3), 0x9cf0ea));
	// CYLINDER //
	((t_lstobject *)lstobj->next)->next = new_obj(TYPE_CYLINDER, new_cylinder(new_vector(0, 1, 5), new_vector(0.2, -0.1, 0.2), 1.5, 15));
	// LIGHTS
	lstlight = new_obj(TYPE_LIGHT, new_default_light(TYPE_AMBIENT, 0.3, 0xffffff));
	lstlight->next = (t_lstobject *)new_obj(TYPE_LIGHT, new_default_light(TYPE_POINT, 0.5, 0xffffff));
	set_vector(((t_light *)((t_lstobject *)lstlight->next)->object)->vector, -3, 1, -1);
	((t_lstobject *)lstlight->next)->next = new_obj(TYPE_LIGHT, new_default_light(TYPE_DIRECTIONAL, 0.1, 0xffffff));
	set_vector(((t_light *)((t_lstobject *)((t_lstobject *)lstlight->next)->next)->object)->vector, 0, -5, -5);
	scene = new_scene(obs, lstobj, lstlight, 0x0); // fill info in scene
	// RENDERING 
	x = -(viewport->width/2) + 1;
	while ((x + (viewport->width/2) <= viewport->width))
	{
		y = -(viewport->height/2);
		while (y < viewport->height/2)
		{
			//printf("(%f, %f) \n", (x + (viewport->width/2)), (y + (viewport->height/2)));
			//printf("reflection sphere 1 is %f\n", ((t_sphere *)lstobj->object)->reflection);
			direction = new_vector(x / viewport->width, y / viewport->height, 1);
			printf("direction is %f %f %f \n", direction->x, direction->y, direction->z);
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
}*/
