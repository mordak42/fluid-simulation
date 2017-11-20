#include <stdlib.h>
#include <math.h>
#include "core/wolf3d.h"
#include "overlay/overlay.h"
#include "overlay/internal_overlay.h"

static inline void			fill_pixel(t_pix *scene, t_coord_i c, t_pix pix)
{
	int offset;

	offset = (c.y * WIDTH) + c.x;
	if (offset >= (WIDTH * HEIGHT) || offset < 0)
		return ;
	scene[offset] = pix;
}

static inline t_pix			get_pix_line(t_line *p, float x,
										float x_beg, float x_end)
{
	t_pix	b_pix;
	t_pix	f_pix;
	t_pix	new_pix;
	float	ratio;

	b_pix = p->b_pix;
	f_pix = p->f_pix;
	ratio = (x - x_beg) / (x_end - x_beg);
	new_pix.c.r = ((1.f - ratio) * b_pix.c.r + ratio * f_pix.c.r);
	new_pix.c.g = ((1.f - ratio) * b_pix.c.g + ratio * f_pix.c.g);
	new_pix.c.b = ((1.f - ratio) * b_pix.c.b + ratio * f_pix.c.b);
	new_pix.c.a = ((1.f - ratio) * b_pix.c.a + ratio * f_pix.c.a);
	return (new_pix);
}

static void					horizontal_line(t_pix *scene, t_line *p,
											t_coord_i inc)
{
	int			cumul;
	t_coord_i	c;
	t_pix		pix;

	cumul = p->d.x / 2;
	c = p->p1;
	while (TRUE)
	{
		c.x += inc.x;
		cumul += p->d.y;
		if (cumul >= p->d.x)
		{
			c.y += inc.y;
			cumul -= p->d.x;
		}
		pix = get_pix_line(p, c.x, p->p1.x, p->p2.x);
		fill_pixel(scene, c, pix);
		if (c.x == p->p2.x)
			break ;
	}
}

static void					vertical_line(t_pix *scene, t_line *p,
											t_coord_i inc)
{
	int			cumul;
	t_coord_i	c;
	t_pix		pix;

	cumul = p->d.y / 2;
	c = p->p1;
	while (TRUE)
	{
		c.y += inc.y;
		cumul += p->d.x;
		if (cumul >= p->d.y)
		{
			c.x += inc.x;
			cumul -= p->d.y;
		}
		pix = get_pix_line(p, c.y, p->p1.y, p->p2.y);
		fill_pixel(scene, c, pix);
		if (c.y == p->p2.y)
			break ;
	}
}

void						draw_line(t_pix *scene, t_line *p)
{
	t_coord_i	inc;

	p->d = (t_coord_i){p->p2.x - p->p1.x, p->p2.y - p->p1.y};
	inc = (t_coord_i){(p->d.x < 0) ? -1 : 1, (p->d.y < 0) ? -1 : 1};
	p->d = (t_coord_i){abs(p->d.x), abs(p->d.y)};
	fill_pixel(scene, p->p1, p->b_pix);
	if (p->d.x == 0 && p->d.y == 0)
		return ;
	if (p->d.x > p->d.y)
		horizontal_line(scene, p, inc);
	else
		vertical_line(scene, p, inc);
}
