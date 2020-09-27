/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:52:14 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 13:14:41 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	sprite_pixel(t_doom *dm, t_gfx gfx, int *yx, int *g)
{
	if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid &&
		yx[0] + g[0] > -1 && yx[1] + g[1] > -1 &&
		gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
		dm->spr[yx[6]].dist < dm->wallarr[dm->winw
		* (yx[0] + g[0]) + (yx[1] + g[1])])
	{
		dm->img.data[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])]
			= color_shift(gfx.data[gfx.wid * (yx[4] + gfx.y)
				+ (yx[5] + gfx.x)],
			dm->spr[yx[6]].dist, dm, 0);
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])]
			= dm->spr[yx[6]].dist;
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
}

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
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])]
			= dm->prj[yx[6]].dist;
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

void	object_pixel(t_doom *dm, t_gfx gfx, int *yx, int *g)
{
	if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid &&
		yx[0] + g[0] > -1 && yx[1] + g[1] > -1 &&
		gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)] != 0xffff00ff &&
		dm->obj[yx[6]].dist < dm->wallarr[dm->winw
		* (yx[0] + g[0]) + (yx[1] + g[1])])
	{
		dm->img.data[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])]
			= color_shift(gfx.data[gfx.wid * (yx[4] + gfx.y) + (yx[5] + gfx.x)],
			dm->obj[yx[6]].dist, dm, 0);
		dm->wallarr[dm->winw * (yx[0] + g[0]) + (yx[1] + g[1])]
			= dm->obj[yx[6]].dist;
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

void	draw_objects(t_doom *dm, int y, int x, double spra)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		spra = atan2(dm->obj[i].dir.y, dm->obj[i].dir.x);
		if (spra < dm->mina || spra > dm->maxa)
			spra += M_PI * 2;
		if (spra < dm->mina || spra > dm->maxa)
			spra -= M_PI * 2;
		dm->obj[i].dist = tri_pythagor(dm->pos, dm->obj[i].pos);
		dm->obj[i].dir.z = (dm->obj[i].pos.z - dm->pos.z) / dm->obj[i].dist;
		dm->obj[i].dir.y = (dm->obj[i].pos.y - dm->pos.y) / dm->obj[i].dist;
		dm->obj[i].dir.x = (dm->obj[i].pos.x - dm->pos.x) / dm->obj[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina)) - ((dm->gfx[dm->obj[i].gfx].wid / 2) * 2 / dm->obj[i].dist);
		y = dm->winh * ((dm->obj[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z)) - ((dm->gfx[dm->obj[i].gfx].hgt / 2) * 2 / dm->obj[i].dist);
		if (i == 0)
			chest_object(dm, i, y, x);
		else if ((i == 1 || i == 2) && dm->drawgunandkeycard)
				draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx], (int[7]){y, x, dm->gfx[dm->obj[i].gfx].hgt, dm->gfx[dm->obj[i].gfx].wid, 0, 0, i}, dm->obj[i].size / dm->obj[i].dist);
		//else
		//	draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx], (int[7]){y, x, dm->gfx[dm->obj[i].gfx].hgt, dm->gfx[dm->obj[i].gfx].wid, 0, 0, i}, dm->obj[i].size / dm->obj[i].dist);
	}
}

void	draw_sprites(t_doom *dm, int y, int x, double spra)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (i == dm->id)
			continue;
		spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x);
		if (spra < dm->mina || spra > dm->maxa)
			spra += M_PI * 2;
		if (spra < dm->mina || spra > dm->maxa)
			spra -= M_PI * 2;
		dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
		if (dm->spr[i].dist < 1)
			continue;
		dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
		dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
		dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina)) -
			((dm->gfx[dm->spr[i].gfx].wid / 2) * 2 / dm->spr[i].dist);
		y = dm->winh * ((dm->spr[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z))
			- ((dm->gfx[dm->spr[i].gfx].hgt / 2) * 2 / dm->spr[i].dist);
		if (i == 5 && (dm->spr[i].hp > 0))
			pokemon_trainer(dm, y, x, i);
		else if (i == 6 && (dm->spr[i].hp > 0))
			pokemon_trainer(dm, y, x, i);
		else if (dm->spr[i].hp > 0)
			draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, dm->gfx[dm->spr[i].gfx].hgt,
				dm->gfx[dm->spr[i].gfx].wid, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
	}
}

void	draw_projectiles(t_doom *dm, int y, int x, double spra)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (i == 1)
			player_shooting(dm, i);
		else if (i == 2)
			ai_shooting(dm, i, 5);
		else if (i == 3)
			ai_shooting(dm, i, 6);//spr[6] is charizard
		//else if (i == 4)
		//	ai_shooting(dm, i, 3);//spr[3] is mantaray
		spra = atan2(dm->prj[i].dir.y, dm->prj[i].dir.x);
		if (spra < dm->mina || spra > dm->maxa)
			spra += M_PI * 2;
		if (spra < dm->mina || spra > dm->maxa)
			spra -= M_PI * 2;
		dm->prj[i].dist = tri_pythagor(dm->pos, dm->prj[i].pos);
		dm->prj[i].dir.z = (dm->prj[i].pos.z - dm->pos.z) / dm->prj[i].dist;
		dm->prj[i].dir.y = (dm->prj[i].pos.y - dm->pos.y) / dm->prj[i].dist;
		dm->prj[i].dir.x = (dm->prj[i].pos.x - dm->pos.x) / dm->prj[i].dist;
		x = dm->winw * ((spra - dm->mina) / (dm->maxa - dm->mina)) -
			((dm->gfx[dm->prj[i].gfx].wid / 2) * 2 / dm->prj[i].dist);
		y = dm->winh * ((dm->prj[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z))
			- ((dm->gfx[dm->prj[i].gfx].hgt / 2) * 2 / dm->prj[i].dist);
		draw_projectile_gfx(dm, dm->gfx[dm->prj[i].gfx],
			(int[7]){y, x, 1000, 1000, 0, 0, i}, 4 / dm->prj[i].dist);
	}
}

void	draw_sprite(t_doom *dm, int y, int x, double spra)
{
	dm->mina = atan2(dm->min.y, dm->min.x);
	dm->maxa = atan2(dm->max.y, dm->max.x);
	if (dm->maxa < dm->mina)
		dm->maxa += M_PI * 2;
	draw_objects(dm, y, x, spra);
	draw_sprites(dm, y, x, spra);
	draw_projectiles(dm, y, x, spra);
	//printf("Screen angle %f %f\nProj angle %f\ndiff %f\nspr0 %f %f\n", mina, maxa, atan2(dm->spr[0].dir.y, dm->spr[4].dir.x) * 180 / M_PI + 180, maxa - mina, atan2(dm->spr[0].dir.y, dm->spr[0].dir.x), dm->spr[0].dist);
}
