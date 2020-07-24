#include <stdio.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_pos
{
    float x;
    float y;
    float z;
}               t_pos;

typedef struct s_ray
{
    t_pos start;
    t_pos direction;

}               t_ray;

typedef struct s_sphere
{
    t_pos position;
    float radius;
    int colour;
}               t_sphere;

t_pos    vectorAdd(t_pos *v1, t_pos *v2)
{
    t_pos result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
    return (result);
}

t_pos    vectorSub(t_pos *v1, t_pos *v2)
{
    t_pos result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return (result);
}

float   vectorDot(t_pos *v1, t_pos *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_pos    vectorScale(float c, t_pos*v)
{
    t_pos result = {v->x * c, v->y * c, v->z * c};
    return (result);
}

void    set_xyz(t_pos *position, float x, float y, float z)
{
    position->x = x;
    position->y = y;
    position->z = z;
}

bool    intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
    float       A;
    float       B;
    float       C;
    float       discr;
    t_pos    dist_ray_sphere;

    dist_ray_sphere = vectorSub(&ray->start, &sphere->position);
    A = vectorDot(&ray->direction, &ray->direction);
    B = 2 * vectorDot(&ray->direction, &dist_ray_sphere); // why &dist ?
    C = vectorDot(&dist_ray_sphere, &dist_ray_sphere) - (sphere->radius * sphere->radius);
    discr = B * B - 4 * A * C;
    if (discr < 0)
        return (false);
    else
        return (true);
}

//bool intersect_ray_square(t_ray *ray,)

void saveppm(char *filename, unsigned char *img, int width, int height)
{
    FILE *f;
    f = fopen(filename, "wb");
    fprintf(f, "P6 %d %d %d\n", width, height, 255);
    fwrite(img, 3, width*height, f);
    fclose(f);
}

int main(int argc, char *argv[])
{
    unsigned char img[3 * WIDTH * HEIGHT];

    t_sphere sphere;
    t_ray ray;
    int x;
    int y;
    bool touch;

    set_xyz(&sphere.position, 600, 400, 100);
//    sphere.position.x = 600;
//    sphere.position.y = 400;
//    sphere.position.z = 100;
    sphere.radius = 100;

    set_xyz(&ray.direction, 0, 0, 1);
//    ray.direction.x = 0;
//    ray.direction.y = 0;
//    ray.direction.z = 1;

    ray.start.z = 0;

    for (y = 0; y < HEIGHT; y++)
    {
        ray.start.y = y;
        for (x = 0; x < WIDTH; x++)
        {
            ray.start.x = x;
            touch = intersect_ray_sphere(&ray, &sphere);
            if (touch)
            {
                img[(x + y * WIDTH) * 3 + 0] = 255;
                img[(x + y * WIDTH) * 3 + 1] = 155;
                img[(x + y * WIDTH) * 3 + 2] = 0;
            }
            else
            {
                img[(x + y * WIDTH) * 3 + 0] = 0;
                img[(x + y * WIDTH) * 3 + 1] = 0;
                img[(x + y * WIDTH) * 3 + 2] = 0;
            }
        }
    }
    saveppm("image_test.ppm", img, WIDTH, HEIGHT);
    return (0);
}