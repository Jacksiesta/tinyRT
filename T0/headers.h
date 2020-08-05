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

typedef struct s_pos2d
{
    float x;
    float y;
}              t_post2d;

typedef struct s_sphere
{
    t_pos position;
    float radius;
    int colour;
}               t_sphere;

typedef struct s_lstobject
{
    int     type;
    void    *object;
    void    *next;
}               t_lstobject;

t_lstobject     *create_obj(int t, void *o)
{
    t_lstobject *obj;

    obj = malloc(sizeof(t_lstobject));
    obj->type = t;
    obj->object = o;
    obj->next = NULL;
    return (obj);
}

//insert (x,y,z) value in a variable
t_pos           *create_pos(float x, float y, float z)
{
    t_pos   *position;

    position = malloc(sizeof(t_pos));
    position->x = x;
    position->y = y;
    position->z = z;
    return (position);
}

t_sphere        *create_sphere(float r, int colour)
{
    t_sphere    *sphere;

    sphere = malloc(sizeof(t_sphere));
    sphere->radius = r;
    sphere->colour = colour;
    sphere->position = create_pos(0, 0, 0);
    return (sphere);
}

float   dot_product(t_pos pos1, t_pos pos2)
{
    return (pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z);
}

t_pos2d     *intersect(t_pos origin, t_pos pixel, void *s)
{
    t_pos       *difference;
    float       k[3];
    float       discriminant;
    t_sphere    sphere;
    t_pos2d     *ret;

    sphere = *(t_sphere *)(s); // what
}