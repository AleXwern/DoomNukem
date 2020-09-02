/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:52:14 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/02 14:07:15 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

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
	int		gy;
	int		gx;

	gy = 0;
	while (gy < gfx.hgt * size && (yx[0] + gy) < dm->winh && gy < yx[2] * size)
	{
		yx[4] = gy * (gfx.hgt / (gfx.hgt * size));
		gx = 0;
		while (gx < gfx.wid * size && (yx[1] + gx) < dm->winw && gx < yx[3] * size)
		{
			yx[5] = gx * (gfx.wid / (gfx.wid * size));
			if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid &&
				gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
				dm->spr[yx[6]].dist < dm->wallarr[dm->winw * (yx[0] + gy) + (yx[1] + gx)])
			{
				dm->img.data[dm->winw * (yx[0] + gy) + (yx[1] + gx)] = gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)];
				dm->wallarr[dm->winw * (yx[0] + gy) + (yx[1] + gx)] = dm->spr[yx[6]].dist;
			}
			gx++;
		}
		gy++;
	}
}

/*void	set_projectile(t_doom *dm)
{
	static int	frm;
	
	if (frm == 0)
	{
		dm->spr[4].hp = 100 * (i + 1);
		dm->spr[4].pos.z = dm->spr[0].pos.z;
		dm->spr[4].pos.y = dm->spr[0].pos.y;
		dm->spr[4].pos.x = dm->spr[0].pos.x;
		dm->spr[4].gfx = 23;
		dm->spr[4].mov.z = dm->spr[0].dir.z * -0.04;
		dm->spr[4].mov.y = dm->spr[0].dir.y * -0.04;
		dm->spr[4].mov.x = dm->spr[0].dir.x * -0.04;
	}
	dm->spr[4].pos.z += dm->spr[0].mov.z;
	dm->spr[4].pos.y += dm->spr[0].mov.y;
	dm->spr[4].pos.x += dm->spr[0].mov.x;
	draw_sprite_gfx(dm, dm->gfx[dm->spr[4].gfx], (int[7]){y, x, 1000, 1000, 0, 0, 4}, 2 / dm->spr[4].dist);
	frm++;
	if (frm > 600)
		frm = 0;
}*/

void	demodraw_sprite(t_doom *dm)
{
	int		x;
	int		y;
	int		i;
	double	mina = atan2(dm->min.y, dm->min.x) * 180 / M_PI + 180;
	double	maxa = atan2(dm->max.y, dm->max.x) * 180 / M_PI + 180;
	double	spra;
	static int	frm;

	i = -1;
	if (mina > maxa)
		maxa += 360;
	while (++i < 5)
	{
		spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x) * 180 / M_PI + 180;
		dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
		dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
		dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
		dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
		//if (dm->spr[i].dist > 5)
		//{
			dm->spr[i].pos.z += dm->spr[i].mov.z;
			dm->spr[i].pos.y += dm->spr[i].mov.y;
			dm->spr[i].pos.x += dm->spr[i].mov.x;
		//}
		if (spra < mina || spra > maxa)
			spra += 360;
		if (spra < mina || spra > maxa)
			spra -= 360;
		//if (spra < mina || spra > maxa)
		//	continue;
		x = dm->winw * ((spra - mina) / (maxa - mina)) - ((dm->gfx[dm->spr[i].gfx].wid / 2) * 2 / dm->spr[i].dist);
		y = dm->winh * ((dm->spr[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z)) - ((dm->gfx[dm->spr[i].gfx].hgt / 2) * 2 / dm->spr[i].dist);
		//printf("%d %d at %f %f %f\ndist %f\n%d %d %d\n", i, dm->spr[i].hp, dm->spr[i].pos.z, dm->spr[i].pos.y, dm->spr[i].pos.x, dm->spr[i].dist, dm->spr[i].gfx, x, y);
		if (y < 0)
		{
			dm->gfx[dm->spr[i].gfx].y -= y;
			y = 0;
		}
		if (x < 0)
		{
			dm->gfx[dm->spr[i].gfx].x -= x;
			x = 0;
		}
		draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 1000, 1000, 0, 0, i}, 2 / dm->spr[i].dist);
		dm->gfx[dm->spr[i].gfx].x = 0;
		dm->gfx[dm->spr[i].gfx].y = 0;
	}
	if (dm->spr[4].dist < 0.5)
		dm->hp -= 5;
	if (frm == 250)
	{
		dm->spr[4].hp = 100 * (i + 1);
		dm->spr[4].pos.z = dm->spr[0].pos.z;
		dm->spr[4].pos.y = dm->spr[0].pos.y;
		dm->spr[4].pos.x = dm->spr[0].pos.x;
		dm->spr[4].gfx = 24;
		dm->spr[4].mov.z = dm->spr[0].dir.z * -0.07;
		dm->spr[4].mov.y = dm->spr[0].dir.y * -0.07;
		dm->spr[4].mov.x = dm->spr[0].dir.x * -0.07;
	}
	frm++;
	if (frm > 250)
		frm = 0;
	printf("Screen angle %f %f\nProj angle %f\ndiff %f\n", mina, maxa, atan2(dm->spr[4].dir.y, dm->spr[4].dir.x) * 180 / M_PI + 180, maxa - mina);
}

void	sprite_set(t_doom* dm)
{
	dm->spr[0].hp = 100;
	dm->spr[0].pos.z = 4.5;
	dm->spr[0].pos.y = 12.42;
	dm->spr[0].pos.x = 12.4;
	dm->spr[0].gfx = 10;
	//spr[0] = dm->spr[0];
	static int i;
	while (++i < 4)
	{
		dm->spr[i].hp = 100 * (i + 1);
		dm->spr[i].pos.z = (rand() % 90) / 10;
		dm->spr[i].pos.y = (rand() % 250) / 10;
		dm->spr[i].pos.x = (rand() % 250) / 10;
		dm->spr[i].gfx = (rand() % 8) + 15;
		//spr[i] = dm->spr[i];
	}
}