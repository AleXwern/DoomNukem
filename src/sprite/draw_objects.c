/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:44:55 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/16 16:02:08 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	object_pixel(t_doom *dm, t_gfx gfx, int *yx, int *g)
{
	int		lgt;
	Uint32	col;

	if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid &&
		yx[0] + g[0] > -1 && yx[1] + g[1] > -1 &&
		gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
		dm->obj[yx[6]].dist < dm->wallarr[dm->winw
		* (yx[0] + g[0]) + (yx[1] + g[1])])
	{
		lgt = get_blocklight(dm, dm->obj[yx[6]].pos);
		col = color_shift((gfx.data[gfx.wid * (yx[4] + gfx.y)
			+ (yx[5] + gfx.x)]), dm->obj[yx[6]].dist, dm, 0);
		col = rl_color(lgt, col);
		dm->img.data[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] = col;
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] =
			dm->obj[yx[6]].dist;
	}
}

void	draw_object_gfx(t_doom *dm, t_gfx gfx, int *yx, double size)
{
	int	gy;
	int	gx;

	gy = 0;
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh && gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw
			&& gx < yx[3] * size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			object_pixel(dm, gfx, yx, (int[2]){gy, gx});
			gx++;
		}
		gy++;
	}
}

/*
**	chest width 197 height 197 per frame
*/

void	draw_object(t_doom *dm, int i, int y, int x)
{
	if (i == 0)
	{
		if (dm->chestopened)
			dm->gfx[dm->obj[i].gfx].x = (dm->obj[i].frame / 8) * 196;
		else
			dm->gfx[dm->obj[i].gfx].x = 0;
		draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx],
			(int[7]){y, x, 197, 197, 0, 0, i}, 3 / dm->obj[i].dist);
		if (dm->chestopened && dm->obj[i].frame < 47)
			dm->obj[i].frame++;
		else if (dm->chestopened && dm->obj[i].frame == 47)
			dm->drawgunandkeycard = 1;
	}
	else
		draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx],
		(int[7]){y, x, dm->gfx[dm->obj[i].gfx].hgt,
		dm->gfx[dm->obj[i].gfx].wid, 0, 0, i},
		dm->obj[i].size / dm->obj[i].dist);
}

void	draw_objects(t_doom *dm, int y, int x, int i)
{
	static double	spra;

	while (++i < 12)
	{
		spra = atan2(dm->obj[i].dir.y, dm->obj[i].dir.x);
		spra = spra_check(dm, spra);
		dm->obj[i].dist = tri_pythagor(dm->pos, dm->obj[i].pos);
		dm->obj[i].dir.z = (dm->obj[i].pos.z - dm->pos.z) / dm->obj[i].dist;
		dm->obj[i].dir.y = (dm->obj[i].pos.y - dm->pos.y) / dm->obj[i].dist;
		dm->obj[i].dir.x = (dm->obj[i].pos.x - dm->pos.x) / dm->obj[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina))
			- ((dm->gfx[dm->obj[i].gfx].wid / 2) * 2 / dm->obj[i].dist);
		y = dm->winh * ((dm->obj[i].dir.z - dm->min.z)
			/ (dm->max.z - dm->min.z)) - ((dm->gfx[dm->obj[i].gfx].hgt
			/ 2) * 2 / dm->obj[i].dist);
		if ((i == 1 || i == 2) && dm->drawgunandkeycard)
			draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx],
			(int[7]){y, x, dm->gfx[dm->obj[i].gfx].hgt,
			dm->gfx[dm->obj[i].gfx].wid, 0, 0, i},
			dm->obj[i].size / dm->obj[i].dist);
		else if (i == 0 || i > 2)
			draw_object(dm, i, y, x);
	}
}
