/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:52:14 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 15:40:21 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	sprite_pixel(t_doom *dm, t_gfx gfx, int *yx, int *g)
{
	int		lgt;
	Uint32	col;

	if (yx[4] + gfx.y < gfx.hgt &&
		yx[5] + gfx.x < gfx.wid &&
		yx[0] + g[0] > -1 &&
		yx[1] + g[1] > -1 &&
		gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
		dm->spr[yx[6]].dist < dm->wallarr[dm->winw *
		(yx[0] + g[0]) + (yx[1] + g[1])])
	{
		col = gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)];
		if (dm->spr[yx[6]].dist >
			dm->winarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])])
			col = avg_color(col, dm->window[dm->winw
				* (yx[0] + g[0]) + (yx[1] + g[1])]);
		lgt = get_blocklight(dm, dm->spr[yx[6]].pos);
		col = color_shift(col, dm->spr[yx[6]].dist, dm, 0);
		col = rl_color(lgt, col);
		dm->img.data[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] = col;
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])] =
			dm->spr[yx[6]].dist;
	}
}

/*
**	int YX values
**	0 = Y start point on screen
**	1 = X start point on screen
**	2 = Y end point in relative to start point gfx.y (1 equals 1 towards Y dir)
**	3 = X end point in relative to start point gfx.x
**	4 = pass 0
**	5 = pass 0
**	pass point like (int[6]){1, 1, 1000, 1000, 0, 0}
*/

void	draw_sprite_gfx(t_doom *dm, t_gfx gfx, int *yx, double size)
{
	int	gy;
	int	gx;

	gy = 0;
	//printf("Test %f %d %f\n", gfx.hgt * size, gfx.hgt, size);
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh
		&& gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw
			&& gx < yx[3] * size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			sprite_pixel(dm, gfx, yx, (int[2]){gy, gx});
			gx++;
		}
		gy++;
	}
	//printf("Expected end %d %d\n", yx[0] + gy, yx[1] + gx);
}

double	spra_check(t_doom *dm, double spra)
{
	if (spra < dm->mina || spra > dm->maxa)
		spra += M_PI * 2;
	if (spra < dm->mina || spra > dm->maxa)
		spra -= M_PI * 2;
	return (spra);
}

void	draw_sprites(t_doom *dm, int y, int x, int i)
{
	double	spra;

	while (++i < SPR)
	{
		if (i == dm->id || dm->spr[i].dead)
			continue;
		spra = spra_check(dm, atan2(dm->spr[i].dir.y, dm->spr[i].dir.x));
		dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos) - 0.2;
		if (dm->spr[i].dist < 0.4)
			continue;
		dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
		dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
		dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina)) -
			14 * SPRSIZE / dm->spr[i].dist;
		y = dm->winh * ((dm->spr[i].dir.z - dm->min.z) / (dm->max.z -
			dm->min.z)) - 18 * SPRSIZE / dm->spr[i].dist;
		if (i > 3)
			foe_ai(dm, &dm->spr[i], (int[2]){y, x}, i);
		else
			plr_status(dm, &dm->spr[i], (int[2]){y, x}, i);
	}
}

void	draw_sprite(t_doom *dm, int y, int x, int i)
{
	dm->mina = atan2(dm->min.y, dm->min.x);
	dm->maxa = atan2(dm->max.y, dm->max.x);
	if (dm->maxa < dm->mina)
		dm->maxa += M_PI * 2;
	while (++i < SPR)
	{
		if (!dm->spr[i].dead || !dm->spr[i].respawn)
			continue;
		dm->spr[i].timer++;
		if (dm->spr[i].timer >= dm->spr[i].respawn)
		{
			dm->spr[i].dead = 0;
			dm->spr[i].timer = 0;
			dm->spr[i].hp = 2;
		}
	}
	draw_objects(dm, y, x, -1);
	draw_sprites(dm, y, x, -1);
	draw_projectiles(dm, y, x, -1);
}
