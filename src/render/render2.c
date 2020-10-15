/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:21:20 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/15 16:28:24 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	adjusted_dda(t_doom *dm)
{
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
	{
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
	{
		dm->sided.y += dm->deltad.y;
		dm->map.y += dm->stepy;
		dm->side = 1;
	}
	else
	{
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz;
		dm->side = 2;
	}
	dm->adj = 1;
}

void	rc_init2(t_doom *dm)
{
	dm->cam.x = 2.0 * dm->x / (double)(dm->winw) - 1.0;
	dm->cam.y = 2.0 * dm->y / (double)(dm->winh) - 1.0;
	dm->rayd.x = dm->dir.x + dm->plane.x * dm->cam.x;
	dm->rayd.y = dm->dir.y + dm->plane.y * dm->cam.x;
	dm->rayd.z = dm->dir.z + dm->plane.z * dm->cam.y;
	dm->map.x = ((int)dm->pos.x);
	dm->map.y = ((int)dm->pos.y);
	dm->map.z = ((int)dm->pos.z);
}

void	rc_init(t_doom *dm)
{
	rc_init2(dm);
	dda_prep(dm);
	dda_sys(dm);
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	//if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
	//	printf("%.16f = (%f - %f + (1 - %d) * 0.5) / %.16f side is %d\n", dm->walldist, dm->map.z, dm->pos.z, dm->stepz, dm->rayd.z, dm->side);
	if (dm->hit != 2 && dm->area[(int)dm->map.z]
		[(int)dm->map.y][(int)dm->map.x].b == 6)
		dm->wincol = 1;
	dm->window[dm->winw * dm->y + dm->x] = 0xffffffff;
	dm->winarr[dm->winw * dm->y + dm->x] = 100;
	if (dm->walldist < LIMN)
		dm->walldist = dm->wallarr[dm->winw * (dm->y - 1) + dm->x];
	//if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
	//	printf("%f\n", dm->walldist);
	//dm->walldist += 0.01;
}

void	side_check(t_doom *dm)
{
	int	delta;

	if (dm->hit == 2)
		return ;
	if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 6)
		return ;
	if (dm->side == 0)
		delta = dm->pos.x - dm->map.x;
	else if (dm->side == 1)
		delta = dm->pos.y - dm->map.y;
	else
		delta = dm->pos.z - dm->map.z;
	if (delta > 0)
		dm->side += 3;
}

void	renthread2(t_doom *dm)
{
	dm->wallarr[dm->winw * dm->y + dm->x] = dm->walldist;
	dm->maparr[dm->winw * dm->y + dm->x] = dm->side + 1 +
		dm->map.z + dm->map.y + dm->map.x;
	if (dm->x == 0 && dm->y == 0)
		dm->dm->min = dm->rayd;
	else if (dm->x == dm->winw - 1 && dm->y == dm->winh - 1)
		dm->dm->max = dm->rayd;
	if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2 && dm->hit != 2)
		dm->img.data[dm->winw * dm->y + dm->x] = 0xfff01111;
	else
	{
		if (dm->hit == 2)
			draw_sky(dm);
		else if (dm->hit == 3)
			dm->img.data[dm->winw * dm->y + dm->x] = 0xff000000;
		else if (dm->side == 2 || dm->side == 5)
			render_floor(dm);
		else
			wall_stripe(dm);
		if (dm->iframe > DFRAME)
			dm->img.data[dm->winw * dm->y + dm->x] =
				avg_color(dm->col, 0xffff0000);
	}
}
