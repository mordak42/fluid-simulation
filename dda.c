#include "dda.h"

#define LEVEL_SET_WIDTH 100
#define LEVEL_SET_HEIGHT 100
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MIN3(X,Y,Z) (MIN(MIN(X,Y), MIN(Y,Z)))

/* retourne le point d'intersection avec le level set */

double cubicInterpolate(double p[4], double s) {
    /* Bridson interpolation */
     return (-0.3 * s + 0.5 * s * s - 0.16 * s * s * s) * p[0]
       + (1 - s * s + 0.5 * (s * s * s - s)) * p[1]
       + (s + 0.5 * (s * s - s * s * s)) *p[2]
       + (0.16 * (s * s * s - s)) * p[3];
}

double bicubicInterpolate(double p[4][4], double x, double y) {
    double arr[4];
    arr[0] = cubicInterpolate(p[0], y);
    arr[1] = cubicInterpolate(p[1], y);
    arr[2] = cubicInterpolate(p[2], y);
    arr[3] = cubicInterpolate(p[3], y);
    return cubicInterpolate(arr, x);
}

double tricubicInterpolate(double p[4][4][4], double x, double y, double z) {
    double arr[4];
    arr[0] = bicubicInterpolate(p[0], x, y);
    arr[1] = bicubicInterpolate(p[1], x, y);
    arr[2] = bicubicInterpolate(p[2], x, y);
    arr[3] = bicubicInterpolate(p[3], x, y);
    return cubicInterpolate(arr, z);
}

float level_set[20][20][20];

double evaluateLevelSet(float3 position)
{
    double points[4][4][4];
    int3 g = {position.x, position.y, position.z};

    for (int k = 0; k < 4; k++) {
        int grid_k = k + g.z - 1;
        for (int j = 0; j < 4; j++) {
            int grid_j = j + g.y - 1;
            for (int i = 0; i < 4; i++) {
                int grid_i = i + g.x - 1;
                if (grid_i >= 0 && grid_i < LEVEL_SET_WIDTH + 1 && grid_j >= 0 && grid_j < LEVEL_SET_HEIGHT)
                    points[k][j][i] = level_set[grid_k][grid_j][grid_i];
                else
                    points[k][j][i] = 0;
            }
        }
    }
    float3 interp = (position - g);
    return tricubicInterpolate(points, interp.x, interp.y, interp.z);
}

double	DDA (float3 pos, float3 dir)
{
    float3	    sideDist;
    float3	    deltaDist;
    int3		stepx = {0, 0, 0};
    int3		stepy = {0, 0, 0};
    int3		stepz = {0, 0, 0};
    int3		wall;
    int         side;

    wall.x = (int)pos.x; //TODO: if outside the cube
    wall.y = (int)pos.y;
    wall.y = (int)pos.z;
    deltaDist.x = norm_vect(dir / dir.x);
    deltaDist.y = norm_vect(dir / dir.y);
    deltaDist.z = norm_vect(dir / dir.z);

    if (dir.x < 0) {
        sideDist.x = (pos.x - (int)pos.x) * deltaDist.x;
        stepx.x = -1;
    }
    else {
        sideDist.x = ((int)pos.x + 1.0 - pos.x) * deltaDist.x;
        stepx.x = 1;
    }
    if (dir.y < 0) {
        stepy.y = -1;
        sideDist.y = (pos.y - (int)pos.y) * deltaDist.y;
    }
    else {
        stepy.y = 1;
        sideDist.y = ((int)pos.y + 1.0 - pos.y) * deltaDist.y;
    }
    if (dir.z < 0) {
        stepz.z = -1;
        sideDist.z = (pos.z - (int)pos.z) * deltaDist.z;
    }
    else {
        stepz.z = 1;
        sideDist.z = ((int)pos.z + 1.0 - pos.z) * deltaDist.z;
    }

    double min;
    while (42)
    {
        min = MIN3(sideDist.x, sideDist.y, sideDist.z); 

        if (sideDist.x > 700 && sideDist.y > 700)
            break ;
        if (sideDist.x == min) {
            side = 0;
            if (evaluateLevelSet(wall + stepx))
                break ;
            sideDist.x += deltaDist.x;
            wall.x += stepx.x;
        }
        else if (sideDist.y == min) {
            side = 1;
            if (evaluateLevelSet(wall + stepy))
                break ;
            sideDist.y += deltaDist.y;
            wall.y += stepy.y;
        }
        else {
            side = 2;
            if (evaluateLevelSet(wall + stepz))
                break ;
            sideDist.z += deltaDist.z;
            wall.z += stepz.z;
        }
    }
    return (side == 0) ? sideDist.x : sideDist.y;
}

/*
   void	wolf(void)
   {
   int				x;
   double			dist_wall;
   t_dda			dda;
   t_double_pos	ray_dir;
   t_double_pos	cam_pos;

   cam_pos = &cam_pos;
   ray_dir = &ray_dir;
   x = 0;
   while (x < SCREEN_WIDTH)
   {
   x = x;
   dist_wall = ft_calc_dist(2 * (double)x / (double)SCREEN_WIDTH - 1, dda);
   if (dist_wall < 600)
   ft_trace_colone(x, dist_wall, dda);
   x++;
   }
   }
   */
