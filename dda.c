#include "dda.h"
#include "libft.h"

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

double evaluate_level_set(vector3d position)
{
    double points[4][4][4];

    for (int k = 0; k < 4; k++) {
        int grid_k = k + gk - 1;
        for (int j = 0; j < 4; j++) {
            int grid_j = j + gj - 1;
            for (int i = 0; i < 4; i++) {
                int grid_i = i + gi - 1;
                if (grid_i >= 0 && grid_i < LEVEL_SET_WIDTH + 1 && grid_j >= 0 && grid_j < LEVEL_SET_HEIGHT)
                    points[k][j][i] = level_set[grid_k][grid_j][grid_i];
                else
                    points[k][j][i] = 0;
            }
        }
    }
    vector3d gpos = vector3d(gi, gj, 0) * DX;
    vector3d interp = (position - gpos) / DX;
    return tricubicInterpolate(points, interp.x, interp.y);
}

double	DDA (float3 pos, float3 dir)
{
    float3	    side_dist;
    float3	    delta_dist;
    int3		step;
    int3		wall;

    wall.x = (int)pos.x; //TODO: if outside the cube
    wall.y = (int)pos.y;
    wall.y = (int)pos.z;
    deltaDist.x = norm_vect(dir / dir.x);
    deltaDist.y = norm_vect(dir / dir.y);
    deltaDist.z = norm_vect(dir / dir.z);

    if (rayDir.x < 0) {
        sideDist.x = (pos.x - (int)pos.x) * deltaDist.x;
        step.x = -1;
    }
    else {
        sideDist.x = ((int)pos.x + 1.0 - pos.x) * deltaDist.x;
        step.x = 1;
    }
    if (rayDir.y < 0) {
        step.y = -1;
        sideDist.y = (pos.y - (int)pos.y) * deltaDist.y;
    }
    else {
        step.y = 1;
        sideDist.y = ((int)pos.y + 1.0 - pos.y) * deltaDist.y;
    }
    if (rayDir.z < 0) {
        step.z = -1;
        sideDist.z = (pos.z - (int)pos.z) * deltaDist.z;
    }
    else {
        step.z = 1;
        sideDist.z = ((int)pos.z + 1.0 - pos.z) * deltaDist.z;
    }

    double min;
    while (42)
    {
        min = MIN_3(sideDist.x, sideDist.y, sideDist.z); 

        if (side_dist.x > 700 && side_dist.y > 700)
            break ;
        if (sideDist.x == min) {
            side = 0;
            if (map[wall.x + step.x][wall.y] > 0)
                break ;
            sideDist.x += deltaDist.x;
            wall.x += step.x;
        }
        else if (sideDist.y == min) {
            side = 1;
            if (map[wall.x + step.x][wall.y] > 0)
                break ;
            sideDist.y += deltaDist.y;
            wall.y += step.y;
            side = 1;
        }
        else {
            if (map[wall.x + step.x][wall.y] > 0)
                break ;
            sideDist.z += deltaDist.z;
            wall.z += step.z;
            side = 1;
        }
    }
    return (side == 0) ? sideDist.x : sideDist.y;
}

/*
   void	ft_wolf(void)
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
