#include <stdio.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vector
{
    float x;
    float y;
    float z;
}               t_vector;

typedef struct s_ray
{
    t_vector start;
    t_vector direction;

}               t_ray;

typedef struct s_pos
{
    float x;
    float y;
    float z;
}               t_pos;

typedef struct s_sphere
{
    t_vector position;
    float radius;
    int colour;
}               t_sphere;

t_vector    vectorAdd(t_vector *v1, t_vector *v2)
{
    t_vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
    return (result);
}

t_vector    vectorSub(t_vector *v1, t_vector *v2)
{
    t_vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return (result);
}

float   vectorDot(t_vector *v1, t_vector *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector    vectorScale(float c, t_vector *v)
{
    t_vector result = {v->x * c, v->y * c, v->z * c};
    return (result);
}

bool    intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
    float       A;
    float       B;
    float       C;
    float       discr;
    t_vector    dist_ray_sphere;

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

    sphere.position.x = 400;
    sphere.position.y = 200;
    sphere.position.z = 100;
    sphere.radius = 100;

    ray.direction.x = 0;
    ray.direction.y = 0;
    ray.direction.z = 1;

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



