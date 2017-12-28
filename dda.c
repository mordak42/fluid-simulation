#include "dda.h"

#define DIM_LSET_X 100
#define DIM_LSET_Y 100
#define DIM_LSET_Z 100

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

    for (int z = 0; z < 4; z++) {
        int grid_z = z + g.z - 1;
        for (int y = 0; y < 4; y++) {
            int grid_y = y + g.y - 1;
            for (int x = 0; x < 4; x++) {
                int grid_x = x + g.x - 1;
                if (grid_x >= 0 && grid_x < DIM_LSET_X + 1 && grid_y >= 0 && grid_y < DIM_LSET_Y && grid_z >= 0 && grid_z < DIM_LSET_Z)
                    points[z][y][x] = level_set[grid_z][grid_y][grid_x];
                else
                    points[z][y][x] = 0;
            }
        }
    }
    float3 interp = (position - g);
    return tricubicInterpolate(points, interp.x, interp.y, interp.z);
}

int3	DDA (float3 pos, float3 dir)
{
    float	    sideDist_x;
    float	    sideDist_y;
    float	    sideDist_z;
    float3	    sideDist_x_vect;
    float3	    sideDist_y_vect;
    float3	    sideDist_z_vect;
    float	    deltaDist_x;
    float	    deltaDist_y;
    float	    deltaDist_z;
    float3	    deltaDist_x_vect;
    float3	    deltaDist_y_vect;
    float3	    deltaDist_z_vect;
    int3		step = {0, 0, 0};
    int3		wall;

    wall.x = (int)pos.x; //TODO: if outside the cube
    wall.y = (int)pos.y;
    wall.y = (int)pos.z;
    deltaDist_x_vect = dir / dir.x;
    deltaDist_x = norm_vect(deltaDistx_vect);
    deltaDist_y_vect = dir / dir.y;
    deltaDist_y = norm_vect(deltaDisty_vect);
    deltaDist_z_vect = dir / dir.z;
    deltaDist_z = norm_vect(deltaDistz_vect);
    float delta;

    if (dir.x < 0) {
        step.x = -1;
        delta = pos.x - (int)pos.x;
    }
    else {
        step.x = 1;
        delta = (int)pos.x + 1.0 - pos.x;
    }
    sideDist_x = delta * deltaDist_x;
    sideDist_x_vect = pos + step.x * delta * deltaDist_x_vect;

    if (dir.y < 0) {
        step.y = -1;
        delta = pos.y - (int)pos.y;
    }
    else {
        step.y = 1;
        delta = (int)pos.y + 1.0 - pos.y;
    }
    sideDist_y = delta * deltaDist_y;
    sideDist_y_vect = pos + step.y * delta * deltaDist_y_vect;

    if (dir.z < 0) {
        step.z = -1;
        delta = pos.z - (int)pos.z;
    }
    else {
        step.z = 1;
        delta = (int)pos.z + 1.0 - pos.z;
    }
    sideDist_z = delta * deltaDist_z;
    sideDist_z_vect = pos + step.z * delta * deltaDist_z_vect;

    double min;
    while (42)
    {
        if (!(wall.x >= 0 && wall.x < DIM_LSET_X + 1 && wall.y >= 0 && wall.y < DIM_LSET_Y && wall.z >= 0 && wall.z < DIM_LSET_Z))
            return 0;
        min = MIN3(sideDist_x, sideDist_y, sideDist_z); 

        if (sideDist_x == min) {
            float a = evaluateLevelSet(wall);
            wall.x += step.x;
            float b = evaluateLevelSet(wall);
            if (a < 0 || b < 0)
                break ;
            sideDist_x += deltaDist_x;
        }
        else if (sideDist_y == min) {
            float a = evaluateLevelSet(wall);
            wall.y += step.y;
            float b = evaluateLevelSet(wall);
            if (a < 0 || b < 0)
                break ;
            sideDist_y += deltaDist_y;
        }
        else {
            float a = evaluateLevelSet(wall);
            wall.z += step.z;
            float b = evaluateLevelSet(wall);
            if (a < 0 || b < 0)
                break ;
            sideDist_z += deltaDist_z;
        }
    }
    return wall;
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
