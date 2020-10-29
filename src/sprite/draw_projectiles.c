/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:00 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/28 16:06:05 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	projectile_pixel(t_doom *dm, t_gfx gfx, int *yx, int *g)
{
	if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid &&
		yx[0] + g[0] > -1 && yx[1] + g[1] > -1 &&
		gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
		dm->prj[yx[6]].dist < dm->wallarr[dm->winw * (yx[0] + g[0])
		+ (yx[1] + g[1])])
	{
		dm->img.data[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] =
			color_shift(gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)],
			dm->prj[yx[6]].dist, dm, 0);
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] =
			dm->prj[yx[6]].dist;
	}
}

void	draw_projectile_gfx(t_doom *dm, t_gfx gfx, int *yx, double size)
{
	int	gy;
	int	gx;

	gy = 0;
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh
		&& gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw
			&& gx < yx[3] * size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			projectile_pixel(dm, gfx, yx, (int[2]){gy, gx});
			gx++;
		}
		gy++;
	}
}

void	draw_projectiles(t_doom *dm, int y, int x, int i)
{
	static double	spra;

	while (++i < SPR)
	{
		if (i < 4)
			player_shooting(dm, dm->id);
		else if (i > 3)
			foe_shooting(dm, &dm->spr[i], &dm->prj[i]);
		if (dm->prj[i].dead)
			continue;
		dm->prj[i].dist = tri_pythagor(dm->pos, dm->prj[i].pos);
		spra = atan2(dm->prj[i].dir.y, dm->prj[i].dir.x);
		spra = spra_check(dm, spra);
		dm->prj[i].dir.z = (dm->prj[i].pos.z - dm->pos.z) / dm->prj[i].dist;
		dm->prj[i].dir.y = (dm->prj[i].pos.y - dm->pos.y) / dm->prj[i].dist;
		dm->prj[i].dir.x = (dm->prj[i].pos.x - dm->pos.x) / dm->prj[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina)) -
			104 / dm->prj[i].dist;
		y = dm->winh * ((dm->prj[i].dir.z - dm->min.z) / (dm->max.z -
			dm->min.z)) - 104 / dm->prj[i].dist;
		draw_projectile_gfx(dm, dm->gfx[24],
			(int[7]){y, x, 1000, 1000, 0, 0, i}, PRJSIZE / dm->prj[i].dist);
	}
}
