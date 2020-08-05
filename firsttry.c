#include "minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct 	s_pos
{
	float x;
	float y;
	float z;
}		t_pos;

typedef struct	s_pos2d
{
	float x;
	float y;	
}		t_pos2d;

typedef struct	s_ray
{
	t_pos position;
	t_pos direction;	
}		t_ray;

typedef struct	s_sphere
{
	t_pos 	*position;
	float 	radius;
	int	color;
}		t_sphere;

typedef struct	s_canvas
{
	int	width;
	int	height;
	int	distance;	
}		t_canvas;

typedef struct s_lstobject
{
	int	type;
	void	*object;
	void	*next;	
}		t_lstobject;

t_lstobject	*create_obj(int t, void *o)
{
	t_lstobject	*obj;
	
	obj = malloc(sizeof(t_lstobject));
	obj->type = t;
	obj->object = o;
	obj->next = NULL;
	return (obj);	
}

// insert (x,y,z) values in t_pos variable + ret pos
t_pos		*create_pos(int x, int y, int z)
{
	t_pos	*position;
	
	position = malloc(sizeof(t_pos));
	position->x = x;
	position->y = y;
	position->z = z;
	return (position);	
}

// insert (x,y) values in t_pos2d variable + ret pos
t_pos2d		*create_pos2d(int x, int y)
{
	t_pos2d	*position;
	
	position = malloc(sizeof(t_pos2d));
	position->x = x;
	position->y = y;
	return (position);	
}

// changes *position's (x,y,z) values
void		set_pos(t_pos *position, int x, int y, int z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

t_sphere	*create_sphere(int radius, int color)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->color = color;
	sphere->position = create_pos(0, 0, 0);
	return (sphere);
}

t_canvas	*create_canvas(int w, int h, int d)
{
	t_canvas	*canvas;
	
	canvas = malloc(sizeof(t_canvas));
	canvas->width = w;
	canvas->height = h;
	canvas->distance = d;
	return (canvas);	
}

int		dot_product(t_pos pos1, t_pos pos2)
{
	return (pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z);
}

t_pos		vectorSub(t_pos *v1, t_pos *v2)
{
	t_pos result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return (result);	
}

double		ft_squrt(int nb)
{
	int x;

	x = 1;
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 0)
		return (nb);
	while ((x * x) < nb)
		x++;
	if ((x * x) == nb)
		return (x);
	return (x);
}

// returns (x,y) of intersections
t_pos2d		*intersect(t_pos origin, t_pos pixel, t_sphere sphere)
{
	t_pos	*difference;
	int	k[3];
	int	discr;
	
	//difference = vectorSub(&origin, sphere.position);
	difference = create_pos(origin.x - pixel.x, origin.y - pixel.y, origin.z - pixel.z);
	k[0] = dot_product(pixel, pixel); //A
	k[1] = 2 * dot_product(*difference, pixel); //B
	k[2] = dot_product(*difference, *difference) - (sphere.radius/2 * sphere.radius/2); //C
	
	discr = k[1] * k[1] - 4 * k[0] * k[2]; // B * B - 4 * A * C
	if (discr < 0) // no intersection
		return (NULL);
	else	
		return (create_pos2d((-k[1] + ft_squrt(discr)) / (2 * k[0]), (-k[1] - ft_squrt(discr)) / (2 * k[0])));	
}

int main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pos		*obs_pos;
	t_pos		*checking_pixel;
	t_pos2d		*pos2d;
	t_canvas	*viewport;
	t_sphere	*sphere;
	int		x;
	int		y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 400, "Salut");

	obs_pos = create_pos(0, 0, 0);
	viewport = create_canvas(300, 300, 0);
	sphere = create_sphere(10, 0xffc0cb);
	set_pos(sphere->position, 350, 350, 1200);
	x = 0;
	while (x < viewport->width)
	{
		y = 0;
		while (y < viewport->height)
		{
			checking_pixel = create_pos(x, y, viewport->distance);
			pos2d = intersect(*obs_pos, *checking_pixel, *sphere);
			printf("pos2d[x] is %f && pos2d[y] is %f\n", pos2d->x, pos2d->y);
			if (!pos2d)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0);
			else
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, sphere->color);
			free(pos2d);
			pos2d = NULL;
			y++;			
		}
		x++;
	}
	mlx_loop(mlx_ptr);
}
