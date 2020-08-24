#ifndef MINI_RT
# define MINI_RT

# ifndef BACKGROUND_COLOR
# define BACKGROUND_COLOR 0x0
#endif

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  <math.h>
//#include "minilibx_opengl_20191021/mlx.h"
#include "mlx.h"
//#include "vector.h"
#include "sphere.h"
#include "canvas.h"
#include "lstobjects.h"
#include "light.h"
#include "scene.h"
#include "intersect.h"
#include "get_next_line.h"
#include "raytracing.h"

float		ft_squrt_bin(float x);

#endif
