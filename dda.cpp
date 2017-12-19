#include "wolf.h"
#include "math.h"
#include "libft.h"

float3	mult_vect( float3 v, float t)
{
	float3	res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

float3	div_vect(float3 v, float t)
{
	float3	res;

	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

float3	add_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x + v.x;
	res.y = u.y + v.y;
	res.z = u.z + v.z;
	return (res);
}

float3	sub_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	return (res);
}

inline float min_component(float3 v)
{
    if (v.x <= v.y && v.x <= v.z)
        return v.x;
    if (v.y <= v.x && v.y <= v.z)
        return v.y;
    return v.z;
}

typedef struct		s_dda
{
	float3        side_dist;
	float3	    delta_dist;
	int       		stepx;
	int       		stepy;
	int       		stepz;
    int             mapx;
    int             mapy;
    int             mapz;
	float3        ray_dir;
}					t_dda;


double	dda(t_dda dda, map)
{
    while (42)
    {
        float minsidedist = min_component(dda.sidedist);
        if (dda.sidedist.x == minaidedist) {
            side = 0;
            if (map[wall.x + dda.stepx][wall.y] > 0)
                break ;
            dda.sidedist.x += dda.deltadist.x;
            wall.x += dda.stepx;
        }
        else if (dda.sidedist.y == minsidedist) {
            side = 1;
            if (map[wall.x][wall.y + dda.stepy] > 0)
                break ;
            dda.sidedist.y += dda.deltadist.y;
            wall.y += dda.stepy;
        }
        else {
            side = 2;
            if (map[wall.x][wall.y + dda.stepy] > 0)
                break ;
            dda.sidedist.z += dda.deltadist.z;
            wall.z += dda.stepz;
        }
        if (dda.wall.x > dimx || )
            break ;
    }
    return (side == 0) ? dda.sidedist.x : dda.sidedist.y;
}

void	initdda(t_dda &dda, float3 pos, float3 dir)
{
    if (dir.x < 0) {
        dda->sidedist.x = (pos.x - (int)pos.x) * dda->deltadist.x;
        dda->stepx = -1;
    }
    else {
        dda->sidedist.x = (1.0 - pos.x + (int)pos.x) * dda->deltadist.x;
        dda->stepx = 1;
    }
    if (dir.y < 0) {
        dda->stepy = -1;
        dda->sidedist.y = (pos.y - (int)pos.y) * dda->deltadist.y;
    }
    else {
        dda->stepy = 1;
        dda->sidedist.y = (1.0 - pos.y + (int)pos.y) * dda->deltadist.y;
    }
    if (dir.z < 0) {
        dda->stepz = -1;
        dda->sidedist.z = (pos.z - (int)pos.z) * dda->deltadist.z;
    }
    else {
        dda->stepz = 1;
        dda->sidedist.z = (1.0 - pos.z + (int)pos.z) * dda->deltadist.z;
    }
}

double	calc_dist(float3 pos, float3 dir)
{
    t_dda           dda;

	/*
	 *     |     /|
	 *     |    / |
	 *     ____/__|
	 *     |  /   | 
	 *     | /    |
	 *     |/     | 
	 *   _/|______|
	 *
	 */
	//1 + ||dir / dirx||^2

	dda.wall.x = (int)pos.x;
	dda.wall.y = (int)pos.y;
	dda.deltadist->x = sqrt(1 + normecarre(divvect(dir, dir.x));
			dda.deltadist->y = sqrt(1 + normecarre(divvect(dir, dir.y));
				dda.deltadist->z = sqrt(1 + normecarre(divvect(dir, dir.z));
					initdda(dda, pos, dir);
					return (dda(dda));
					}
