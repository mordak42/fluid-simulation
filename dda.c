#include "dda.h"

float level_set[20][20][20];

#define DIM_LSET_X 20
#define DIM_LSET_Y 20
#define DIM_LSET_Z 20

#define RED 0xFF0000

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
                if (grid_x >= 0 && grid_x < DIM_LSET_X && grid_y >= 0 && grid_y < DIM_LSET_Y && grid_z >= 0 && grid_z < DIM_LSET_Z)
                    points[z][y][x] = level_set[grid_z][grid_y][grid_x];
                else
                    points[z][y][x] = 0;
            }
        }
    }
    float3 interp = (position - g);
    return tricubicInterpolate(points, interp.x, interp.y, interp.z);
}

int outOfRange(float3 pos) {
    if (!(pos.x >= 0 && pos.x < DIM_LSET_X && pos.y >= 0 && pos.y < DIM_LSET_Y && pos.z >= 0 && pos.z < DIM_LSET_Z))
        return 0;
}
/* for now, retourne la couleur du mur */

int 	DDA (float3 pos, float3 dir)
{
    float	    sideDist_x; // longueur accumule sur les intersection avec x=k
    float	    sideDist_y;
    float	    sideDist_z;
    float3	    sideDist_x_vect; // vecteur acummule sur les intersection avec x=k
    float3	    sideDist_y_vect;
    float3	    sideDist_z_vect;
    float	    deltaDist_x; // longueur entre 2 intersection avec x=k et x=k+1
    float	    deltaDist_y;
    float	    deltaDist_z;
    float3	    deltaDist_x_vect; // vecteur entre 2 intersection avec x=k et x=k+1
    float3	    deltaDist_y_vect;
    float3	    deltaDist_z_vect;
    int3		step = {0, 0, 0};

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
        min = MIN3(sideDist_x, sideDist_y, sideDist_z); 

        if (sideDist_x == min) {
            if (outOfRange(sideDist_x_vect))
                return 0;
            float a = evaluateLevelSet(sideDist_x_vect);
            sideDist_x_vect += deltaDist_x_vect;
            float b = evaluateLevelSet(sideDist_x_vect);
            if (a < 0 || b < 0)
                return RED;
            sideDist_x += deltaDist_x;
        }
        else if (sideDist_y == min) {
            if (outOfRange(sideDist_y_vect))
                return 0;
            float a = evaluateLevelSet(sideDist_y_vect);
            sideDist_y_vect += deltaDist_y_vect;
            float b = evaluateLevelSet(sideDist_y_vect);
            if (a < 0 || b < 0)
                return RED;
            sideDist_y += deltaDist_y;
        }
        else {
            if (outOfRange(sideDist_z_vect))
                return 0;
            float a = evaluateLevelSet(sideDist_z_vect);
            sideDist_z_vect += deltaDist_z_vect;
            float b = evaluateLevelSet(sideDist_z_vect);
            if (a < 0 || b < 0)
                return RED;
            sideDist_z += deltaDist_z;
        }
    }
    return 0;
}

void    boule_level_set() {
    float3 centre = {DIM_LSET_X / 2, DIM_LSET_Y / 2, DIM_LSET_Z / 2};
    float RAYON = 3;

    for (int z = 0; z < DIM_LSET_Z; z++) {
        for (int y = 0; y < DIM_LSET_Y; y++) {
            for (int x = 0; x < DIM_LSET_X; x++) {
                float3 point = {x, y, z};
                level_set[z][y][x] = normeVect(point - centre) - RAYON;
            }
        }
    }
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
