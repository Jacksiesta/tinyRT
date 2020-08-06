#include "minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct 	s_pos
{
	double x;
	double y;
	double z;
}		t_pos;

typedef struct	s_pos2d
{
	double x;
	double y;	
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
	double	width;
	double	height;
	double	distance;	
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
t_pos		*create_pos(double x, double y, double z)
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
void		set_pos(t_pos *position, double x, double y, double z)
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

double		ft_squrt_bin(int nb, int p)
{
	int 	left;
	int 	right;
	int 	mid;
	float 	res;
	float 	incr;
	int	x;

	right = nb;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid * mid == nb)
		{
			res = mid;
			break; //	
		}
		if (mid * mid < nb)
		{
			left = mid + 1;
			res = mid;	
		}
		else
			right = mid + 1;
	}
	incr = 0.1;
	while (x < p)
	{
		while (res * res <= nb)
			res += incr;
		res -= incr;
		incr /= 10;
		x++;	
	}
}


// returns (x,y) of intersections
t_pos2d		*intersect(t_pos origin, t_pos pixel, void *s)
{
	t_pos		*difference;
	double		k[3];
	double		discr;
	t_sphere	sphere;
	t_pos2d		*ret;
	
	//sphere = *(t_sphere*)(s);
	difference = create_pos(origin.x - sphere.position->x, origin.y - sphere.position->y, origin.z - sphere.position->z);
	k[0] = dot_product(pixel, pixel); //A
	k[1] = 2 * dot_product(*difference, pixel); //B
	k[2] = dot_product(*difference, *difference) - (sphere.radius * sphere.radius); //C
	
	discr = k[1] * k[1] - 4 * k[0] * k[2]; // B * B - 4 * A * C
	if (discr < 0) // no intersection
		return (NULL);
	return(create_pos2d((-k[1] + ft_squrt(discr)) / (2 * k[0]), (-k[1] - ft_squrt(discr)) / (2 * k[0])));
	free(difference);
	//return (ret);
}

/*
bool	intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
	float 	A;
	float 	B;
	float 	C;
	float	discr;
	t_pos	dist_r_sph;
	
	dist_r_sph = vectorSub(&ray->position, sphere->position);
	A = dot_product(ray->direction, ray->direction);
	B = 2 * dot_product(ray->direction, dist_r_sph);
	C = dot_product(dist_r_sph, dist_r_sph) - (sphere->radius * sphere->radius);
	discr = B * B - 4 * A * C;
	if (discr < 0)
		return (false);
	else
		return (true);
}*/

int main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pos		*obs_pos;
	t_pos		*pix;
	t_pos2d		*pos2d;
	t_canvas	*viewport;
	t_sphere	*sphere;
	int		x;
	int		y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 400, "Wouhou");

	obs_pos = create_pos(0, 0, 0);
	viewport = create_canvas(380, 380, 0);
	sphere = create_sphere(50, 0xffc0cb);
	set_pos(sphere->position, 100, 100, 100);
	x = 0;
	while (x < 400)
	{
		y = 0;
		while (y < 400)
		{
			pix = create_pos(x, y, viewport->distance);
			pos2d = intersect(*obs_pos, *pix, sphere);
			//printf("pos2d is %f && %f", pos2d->x, pos2d->y);
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

















/*
int main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	//t_pos		*obs_pos;
	t_sphere	sphere;
	int		x;
	int		y;
	bool		touch;
	t_ray		ray;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "Oui");
	set_pos(&sphere.position, 200, 200, 100);
	//sphere = *create_sphere(50, 0x87ceff);
	sphere.radius = 50;
	sphere.color = 0xffc0cb;
	printf("oui\n");
	set_pos(&ray.direction, 0, 0, 1);
	ray.position.z = 0;
	y = 0;
	while (y < 600)
	{
		ray.position.y = y;
		x = 0;
		while (x < 600)
		{
			ray.position.x = x;
			touch = intersect_ray_sphere(&ray, &sphere);
			if (!touch)
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0);	
			else
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, sphere.color);	
			
			x++;	
		}
		y++;
		
	}
	mlx_loop(mlx_ptr);
}*/

