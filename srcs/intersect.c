#include "../includes/miniRT.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object)
{
	float	temp;
	float	A;
	float	B;
	float	touch;
	
	touch = 0;
	temp = dot_vector(*object->normal, *object->point);
	A = temp - dot_vector(origin, *object->normal);
	B = dot_vector(direction, *object->normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	printf("touch is %f\n", touch);
	return (touch);
}

float	intersect_square(t_vector origin, t_vector direction, t_square *sq)
{
	t_vector	*point;
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*ap;
	t_vector	*normal;
	t_vector	*var;
	float		A;
	float		B;
	float		X;
	float		Y;
	float		temp;
	float		touch;

	ab = sub_vector(*sq->b, *sq->a);
	ac = sub_vector(*sq->c, *sq->a);
	// cross prod of (ab x ac) to get normal 
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->z * ac->x - ab->x * ac->z, ab->y * ac->z - ab->z * ac->y);
	temp = dot_vector(*normal, *sq->center);
	A = temp - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	var = scale_vector(touch, direction);
	point = add_vector(origin, *var);
	free(var);
	ap = sub_vector(*point, *sq->a);
	X = dot_vector(*ap, *ac) / dot_vector(*ac, *ac);
	Y = dot_vector(*ap, *ab) / dot_vector(*ab, *ab);
	if (X >= 0 && X <= 1 && Y >= 0 && Y <= 1)
		return (touch);
	return (0); 
}
/*
float	intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr)
{
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*normal;
	t_vector	*var;
	t_vector	*point;
	t_vector	*p;
	float		A;
	float		B;
	float		C;
	float		D;
	float		E;
	float		denom;
	float		touch;
	float		r1;
	float		r2;
	
	ab = sub_vector(*tr->b, *tr->a);
	ac = sub_vector(*tr->c, *tr->a);
	//cross prod of (ab x ac) to get normal
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->y * ac->z - ab->z * ac->y, ab->z * ac->x - ab->x * ac->z);
	C = dot_vector(*normal, *tr->a);
	A = C - dot_vector(*normal, *tr->a);
	B = dot_vector(direction, *normal);
	touch = A / B;
	printf("touch is %f\n", touch);
	if (touch < 0)
		return (0);
	var = scale_vector(touch, direction);
	point = add_vector(origin, *var);
	free(var);
	p = sub_vector(*point, *tr->a);
	A = dot_vector(*ab, *ab);
	B = dot_vector(*ab, *ac);
	C = dot_vector(*ac, *ac);
	D = dot_vector(*p, *ab);
	E = dot_vector(*p, *ac);
	denom = B * B - A * C;
	r1 = (B * E - C * D) / denom;
	if (r1 < 0 || r1 > 1)
		return (0);
	r2 = (B * D - A * E) / denom;
		return (0);
	return (touch);
}*/

float		intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr)
{
	t_vector 	*point;
	t_vector 	*temp;
	float 		denom;
	float 		A;
	float		B;
	float 		touch;
	t_vector 	*u;
	t_vector 	*v;
	t_vector 	*w;
	t_vector 	*normal;
	float 		r1;
	float		r2;
	float		uu;
	float		uv;
	float		vv;
	float		wu;
	float		wv;
	
	u = sub_vector(*tr->b, *tr->a);
	v = sub_vector(*tr->c, *tr->a);
	normal = cross_product(*u, *v);
	denom = dot_vector(*normal, *tr->a);
	A = denom - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	temp = scale_vector(touch, direction);
	point = add_vector(origin, *temp);
	free(temp);
	w = sub_vector(*point, *tr->a);
	uu = dot_vector(*u, *u);
	uv = dot_vector(*u, *v);
	vv = dot_vector(*v, *v);
	wu = dot_vector(*w, *u);
	wv = dot_vector(*w, *v);
	denom = uv * uv - uu * vv;
	r1 = (uv * wv - vv * wu) / denom;
	if (r1 < 0 || r1 > 1)
		return (0);
	r2 = (uv * wu - uu * wv) / denom;
	if (r2 < 0 || (r2 + r1 > 1))
		return (0);
	return (touch);
}

// i = -1 if inverse of ray needed , otherwise 1
float		calc_discr(t_cylinder *cy, t_vector *point, t_vector *p, int i)
{
	float 		A;
	float 		B;
	float 		C;
	t_vector 	*m;
	
	C = dot_vector(*cy->orientation, *p);
	A = C - dot_vector(*point, *cy->orientation);
	m = scale_vector(i, *cy->orientation);
	B = dot_vector(*m, *cy->orientation);
	C = A / B;
	return (C);	
}

float		intersect_cyl(t_vector origin, t_vector direction, t_cylinder *cy)
{
	float 		A;
	float 		B;
	float 		C;
	float 		D;
	t_vector 	*temp;
	t_vector 	*temp2;
	t_vector 	*point;
	t_vector 	*point_tmp;
	float 		d[4];
	float 		ret;
	float 		size;

	temp = sub_vector(origin, *cy->center);
	d[0] = 1 / dot_vector(*cy->orientation, *cy->orientation);
	d[1] = dot_vector(direction, *cy->orientation);
	d[2] = dot_vector(*temp, *temp);
	d[3] = dot_vector(*cy->orientation, *temp);
	A = dot_vector(direction, direction) - (d[1] * d[1] * d[0]);
	B = 2.0 * (dot_vector(direction, *temp)) - (2 * d[1] * d[3] * d[0]);
	C = d[2] - ((cy->diameter / 2) * (cy->diameter / 2)) - ((d[3] * d[3]) * d[0]);
	free(temp);
	D = (B * B) - (4 * A * C);
	if (D < 0)
		return (0);
	d[0] = (- B + sqrt(D)) / (2.0 * A);
	d[1] = (- B - sqrt(D)) / (2.0 * A);
	ret = (d[0] < d[1]) ? d[0] : d[1];
	if (ret == 0)
		return (0);
	//printf("size vs height %f +++ %f \n", size, object->height);
	//printf("point 1 coord (%f, %f, %f)\n", object->point1->x, object->point1->y, object->point1->z);
	//printf("point 2 coord (%f, %f, %f)\n", object->point2->x, object->point2->y, object->point2->z);
	//printf("cylinder center is (%f, %f, %f)\n", object->center->x, object->center->y, object->center->z);
	size = distance_points(*cy->point1, *cy->point2);
	temp = scale_vector(ret, direction);
	point = add_vector(origin, *temp);
	free(temp);

	//C = dot_vector(*object->orientation, *object->point1);
	//A = C - dot_vector(*point, *object->orientation);
	//B = dot_vector(*object->orientation, *object->orientation);
	//C = A / B;
	temp = scale_vector(calc_discr(cy, point, cy->point1, 1), *cy->orientation);
	point_tmp = add_vector(*point, *temp);
	free(temp);
	d[2] = distance_points(*point, *point_tmp);
	free(point_tmp);

	temp2 = scale_vector(-1, *cy->orientation);
	temp = scale_vector(calc_discr(cy, point, cy->point2, -1), *temp2);
	//C = dot_vector(*cy->orientation, *cy->point2);
	//A = C - dot_vector(*point, *cy->orientation);
	//temp2 = scale_vector(-1, *cy->orientation);
	//B = dot_vector(*temp2, *cy->orientation);
	//C = A / B;
	//temp = scale_vector(C, *temp2);
	point_tmp = add_vector(*point, *temp);
	free(temp2);
	free(temp);
	d[3] = distance_points(*point, *point_tmp);
	free(point_tmp);
	free(point);

	C = dot_vector(*cy->orientation, *cy->point1);
	A = C - dot_vector(origin, *cy->orientation);
	B = dot_vector(direction, *cy->orientation);
	C = A / B;
	//C = calc_discr(cy, point, cy->point1, 1);
	if (C > 0)
	{
		temp = scale_vector(C, direction);
		point = add_vector(origin, *temp);
		free(temp);
		d[0] = distance_points(*point, *cy->point1);
		free(point);
		if (d[0] < cy->diameter / 2)
		{
			if (!(d[2] > size || d[3] > size))
				return (ret);
			return (C);
		}
	}
	C = dot_vector(*cy->orientation, *cy->point2);
	A = C - dot_vector(origin, *cy->orientation);
	B = dot_vector(direction, *cy->orientation);
	C = A / B;
	//C = calc_discr(cy, point, cy->point1, 1);
	// cap //
	if (C > 0)
	{
		temp = scale_vector(C, direction);
		point = add_vector(origin, *temp);
		free(temp);
		d[0] = distance_points(*point, *cy->point2);
		free(point);
		if (d[0] < cy->diameter / 2)
		{
			if (!(d[2] > size || d[3] > size))
				return (ret);
			return (C);
		}
	}
	if ((d[2] > size || d[3] > size))
		return (0);
	return (ret);
}
