/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:52:14 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/18 16:30:43 by tbergkul         ###   ########.fr       */
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
			if (yx[4] + gfx.y < gfx.hgt && yx[5] + gfx.x < gfx.wid && yx[0] + gy > -1 && yx[1] + gx > -1 &&
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

void	chest_sprite(t_doom *dm, int i, int y, int x)
{
	//chest width 197 height 197 per frame
	if (dm->chestopened)
		dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 196;
	else
		dm->gfx[dm->spr[i].gfx].x = 0;
	draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 197, 197, 0, 0, i}, 3 / dm->spr[i].dist);
	if (dm->chestopened && dm->spr[i].frame < 47)
		dm->spr[i].frame++;
	else if (dm->chestopened && dm->spr[i].frame == 47)
		dm->drawgunandkeycard = 1;
}

void	ai_movement(t_doom *dm, t_sprite *s)
{
	// "HASA" (Highly Advanced Super Ai)
	if (s->move == 'a')//alerted
	{
		if (dm->gfx[s->gfx].y == 48 || dm->gfx[s->gfx].y == 96)
			dm->gfx[s->gfx].y = 0;
		s->move = 'm';
	}
	else if (s->move == 'm')//moving
	{
		//s->face.y = -s->dir.y;
		//s->face.x = -s->dir.x;
		if (dm->area[(int)s->pos.z][(int)s->pos.y][(int)(s->pos.x + s->mov.x)].b <= 1)
		{
			//printf("moving on: %f  %f  %f\n", s->pos.z, s->pos.y, (s->pos.x + s->mov.x));
			s->pos.x += s->mov.x;
		}
		if (dm->area[(int)s->pos.z][(int)(s->pos.y + s->mov.y)][(int)s->pos.x].b <= 1)
			s->pos.y += s->mov.y;
	}
}

void	ai_shooting(t_doom *dm, int y, int x)
{
	static int	frm;

	if (frm == 0 && !dm->prj[0].pos.x && dm->spr[8].move == 's')
	{
		//printf("0 prj created\n");
		dm->prj[0].pos.z = dm->spr[8].pos.z;
		dm->prj[0].pos.y = dm->spr[8].pos.y;
		dm->prj[0].pos.x = dm->spr[8].pos.x;
		dm->prj[0].gfx = 24;
		dm->prj[0].mov.z = dm->spr[8].dir.z * -0.03;
		dm->prj[0].mov.y = dm->spr[8].dir.y * -0.03;
		dm->prj[0].mov.x = dm->spr[8].dir.x * -0.03;
	}
	if (frm == 100 && !dm->prj[1].pos.x && dm->spr[8].move == 's')
	{
		//printf("1 prj created\n");
		dm->prj[1].pos.z = dm->spr[8].pos.z;
		dm->prj[1].pos.y = dm->spr[8].pos.y;
		dm->prj[1].pos.x = dm->spr[8].pos.x;
		dm->prj[1].gfx = 24;
		dm->prj[1].mov.z = dm->spr[8].dir.z * -0.03;
		dm->prj[1].mov.y = dm->spr[8].dir.y * -0.03;
		dm->prj[1].mov.x = dm->spr[8].dir.x * -0.03;
	}
	if (dm->prj[0].pos.x)
	{
		//printf("0 prj moving\n");
		dm->prj[0].pos.z += dm->prj[0].mov.z;
		dm->prj[0].pos.y += dm->prj[0].mov.y;
		dm->prj[0].pos.x += dm->prj[0].mov.x;
		draw_sprite_gfx(dm, dm->gfx[dm->prj[0].gfx], (int[7]){y, x, 1000, 1000, 0, 0, 4}, 2 / dm->prj[0].dist);
	}
	if (dm->prj[1].pos.x)
	{
		//printf("1 prj moving\n");
		dm->prj[1].pos.z += dm->prj[1].mov.z;
		dm->prj[1].pos.y += dm->prj[1].mov.y;
		dm->prj[1].pos.x += dm->prj[1].mov.x;
		draw_sprite_gfx(dm, dm->gfx[dm->prj[1].gfx], (int[7]){y, x, 1000, 1000, 0, 0, 4}, 2 / dm->prj[1].dist);
	}
	frm++;
	if (frm > 200)
		frm = 0;
	if (dm->prj[0].dist < 0.3)
	{
		//printf("0 prj hit player\n");
		//dm->hp -= 1;
		ft_bzero(&dm->prj[0], sizeof(t_sprite));
	}
	else if (dm->area[(int)dm->prj[0].pos.z][(int)dm->prj[0].pos.y][(int)dm->prj[0].pos.z].b > 1)
	{
		//printf("0 prj hit wall\n");
		ft_bzero(&dm->prj[0], sizeof(t_sprite));
	}
}

void	pokemon_trainer(t_doom *dm, int y, int x, double spra)
{
	double	sprb;
	int		i;

	i = 8;
	//pokemon width 32 height 48 per frame
	if (dm->spr[i].move != 'x')
		dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 32;
	else
		dm->gfx[dm->spr[i].gfx].x = 0;
	dm->spr[i].face = dm->spr[i].dir;////
	if (dm->spr[i].move == 'x')
	{
		spra = atan2(dm->spr[i].face.y, dm->spr[i].face.x) * 180 / M_PI + 180;
		sprb = atan2(0, 1) * 180 / M_PI + 180;
		sprb = sprb - spra;
		//printf("sprb: %f\n", sprb);
		if (sprb < 45 && sprb > -45)
			dm->gfx[dm->spr[i].gfx].y = 0;
		else if (sprb > 135 || sprb < -135)
			dm->gfx[dm->spr[i].gfx].y = 144;
		else if (sprb >= 45)
			dm->gfx[dm->spr[i].gfx].y = 48;
		else
			dm->gfx[dm->spr[i].gfx].y = 96;
	}
	if (dm->spr[i].dist <= 6 && dm->spr[i].dist >= 2.5)
	{
		if (dm->gfx[dm->spr[i].gfx].y != 144 && dm->spr[i].move != 'm'/* && you can see the sprite*/)
			dm->spr[i].move = 'a';//alerted
		dm->spr[i].mov.x = dm->spr[i].dir.x * -0.03;
		dm->spr[i].mov.y = dm->spr[i].dir.y * -0.03;
	}
	else if (dm->spr[i].dist <= 2.5 /* && you can see the sprite*/)
	{
		dm->spr[i].move = 's';//shooting
		dm->gfx[dm->spr[i].gfx].x = 0;
		dm->gfx[dm->spr[i].gfx].y = 0;
	}
	else
		dm->spr[i].move = 'x';//stand still
	ai_movement(dm, &dm->spr[i]);
	ai_shooting(dm, y, x);
	//printf("poke face: %f  %f  %f\n", dm->spr[i].face.z, dm->spr[i].face.y, dm->spr[i].face.x);
	draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 48, 32, 0, 0, i}, 25 / dm->spr[i].dist);
	dm->spr[i].frame++;
	if (dm->spr[i].frame == 32)
		dm->spr[i].frame = 0;
}

void	draw_sprite(t_doom *dm, int y, int x, double spra)
{
	int			i;
	static int	frm;
	double		mina = atan2(dm->min.y, dm->min.x);
	double		maxa = atan2(dm->max.y, dm->max.x);

	i = -1;
	if (maxa < mina)
		maxa += M_PI * 2;
	while (++i < 9)
	{
		spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x);
		if (spra < mina || spra > maxa)
			spra += M_PI * 2;
		if (spra < mina || spra > maxa)
			spra -= M_PI * 2;
		dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
		dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
		dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
		dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
		x = dm->winw * ((spra - mina) / (maxa - mina)) - ((dm->gfx[dm->spr[i].gfx].wid / 2) * 2 / dm->spr[i].dist);
		//dm->spr[i].dist += (1.0 * dm->winw / 2 - abs(dm->winw / 2 - x)) / dm->winw;
		y = dm->winh * ((dm->spr[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z)) - ((dm->gfx[dm->spr[i].gfx].hgt / 2) * 2 / dm->spr[i].dist);
		if (i == 5 || i == 6)
		{
			if (dm->drawgunandkeycard)
				draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, dm->gfx[dm->spr[i].gfx].hgt, dm->gfx[dm->spr[i].gfx].wid, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
		}
		else if (i == 7)
			chest_sprite(dm, i, y, x);
		else if (i == 8)
			pokemon_trainer(dm, y, x, spra);
		else
			draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, dm->gfx[dm->spr[i].gfx].hgt, dm->gfx[dm->spr[i].gfx].wid, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
	}
	//printf("Screen angle %f %f\nProj angle %f\ndiff %f\nspr0 %f %f\n", mina, maxa, atan2(dm->spr[0].dir.y, dm->spr[4].dir.x) * 180 / M_PI + 180, maxa - mina, atan2(dm->spr[0].dir.y, dm->spr[0].dir.x), dm->spr[0].dist);
}

/*void	demodraw_sprite(t_doom *dm)
{
	int		x;
	int		y;
	int		i;
	double	mina = atan2(dm->min.y, dm->min.x) * 180 / M_PI + 180;
	double	maxa = atan2(dm->max.y, dm->max.x) * 180 / M_PI + 180;
	double	spra;
	double	sprb;
	static int	frm;

	i = -1;
	if (mina > maxa)
		maxa += 360;
	while (++i < 8)
	{
		spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x) * 180 / M_PI + 180;
		dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
		dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
		dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
		dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;

		if (spra < mina || spra > maxa)
			spra += 360;
		if (spra < mina || spra > maxa)
			spra -= 360;
		x = dm->winw * ((spra - mina) / (maxa - mina)) - ((dm->gfx[dm->spr[i].gfx].wid / 2) * 2 / dm->spr[i].dist);
		y = dm->winh * ((dm->spr[i].dir.z - dm->min.z) / (dm->max.z - dm->min.z)) - ((dm->gfx[dm->spr[i].gfx].hgt / 2) * 2 / dm->spr[i].dist);
		if (x < 0)
		{
			dm->gfx[dm->spr[i].gfx].x -= x;
			x = 0;
		}
		if (y < 0)
		{
			dm->gfx[dm->spr[i].gfx].y -= y;
			y = 0;
		}
		if (i == 5 || i == 6)
		{
			if (dm->drawgunandkeycard)
				draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, dm->gfx[dm->spr[i].gfx].hgt, dm->gfx[dm->spr[i].gfx].wid, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
		}
		else if (i == 7)
		{
			if (dm->chestopened)
				dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 196;
			else
				dm->gfx[dm->spr[i].gfx].x = 0;
			if (dm->chestopened && dm->spr[i].frame < 47)
				dm->spr[i].frame++;
			else if (dm->chestopened && dm->spr[i].frame == 47)
				dm->drawgunandkeycard = 1;
			draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 197, 197, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
		}
		else
			draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, dm->gfx[dm->spr[i].gfx].hgt, dm->gfx[dm->spr[i].gfx].wid, 0, 0, i}, dm->spr[i].size / dm->spr[i].dist);
		dm->gfx[dm->spr[i].gfx].x = 0;
		dm->gfx[dm->spr[i].gfx].y = 0;
	}
	if (dm->spr[4].dist < 0.5)
	{
		dm->hp -= 40;
		ft_bzero(&dm->spr[4], sizeof(t_sprite));
	}
	else if (dm->area[(int)dm->spr[4].pos.z][(int)dm->spr[4].pos.y][(int)dm->spr[4].pos.z].b > 1)
		ft_bzero(&dm->spr[4], sizeof(t_sprite));
	if (frm == 350)
	{
		dm->spr[4].hp = 100 * (i + 1);
		dm->spr[4].pos.z = dm->spr[0].pos.z;
		dm->spr[4].pos.y = dm->spr[0].pos.y;
		dm->spr[4].pos.x = dm->spr[0].pos.x;
		dm->spr[4].gfx = 24;
		dm->spr[4].mov.z = dm->spr[0].dir.z * -0.4;
		dm->spr[4].mov.y = dm->spr[0].dir.y * -0.4;
		dm->spr[4].mov.x = dm->spr[0].dir.x * -0.4;
	}
	if (frm < 150)
		dm->spr[0].gfx = 35;
	else
		dm->spr[0].gfx = 34;
	frm++;
	if (frm > 350)
		frm = 0;
	//printf("Screen angle %f %f\nProj angle %f\ndiff %f\n", mina, maxa, atan2(dm->spr[4].dir.y, dm->spr[4].dir.x) * 180 / M_PI + 180, maxa - mina);
}*/

void	sprite_set(t_doom* dm)
{
	static int	i;
	double		mov;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0 || mov < -1.0)
		mov /= fabs(mov) * 2;

	if (i)
		return;
	dm->spr[0].hp = 100;
	dm->spr[0].pos.z = 7.2;
	dm->spr[0].pos.y = 12.42;
	dm->spr[0].pos.x = 12.4;
	dm->spr[0].gfx = 34;
	dm->spr[0].size = 1;
	//spr[0] = dm->spr[0];
	while (++i < 4)
	{
		dm->spr[i].hp = 100 * (i + 1);
		dm->spr[i].pos.z = (rand() % 90) / 10;
		dm->spr[i].pos.y = (rand() % 250) / 10;
		dm->spr[i].pos.x = (rand() % 250) / 10;
		dm->spr[i].gfx = (rand() % 8) + 15;
		dm->spr[i].size = 1;
		//spr[i] = dm->spr[i];
	}

	// PokemonTrainer
	dm->spr[8].hp = 100;
	dm->spr[8].pos.z = 6.6;
	dm->spr[8].pos.y = 12.4;
	dm->spr[8].pos.x = 16.4;
	dm->spr[8].gfx = 32;
	dm->spr[8].move = 'x';
	//dm->spr[8].steps = 0;//not needed
	dm->spr[8].frame = 0;
	dm->spr[8].size = 5;
	dm->spr[8].face.x = 0;//use this as a "which direction is the trainer facing"
	/*dm->spr[8].pos.z = 1.51;
	dm->spr[8].pos.y = 4.51;
	dm->spr[8].pos.x = 4.51;*/
	//dm->spr[8].mov.x = 0.02;
	//dm->spr[8].mov.y = 0.02;

	// Keycard
	//dm->spr[5].pos.z = 3.0;
	//dm->spr[5].pos.y = 6.0;
	//dm->spr[5].pos.x = 7.5;
	dm->spr[5].pos.z = 8.0;
	dm->spr[5].pos.y = 2.8;
	dm->spr[5].pos.x = 20.5;
	dm->spr[5].gfx = 30;
	dm->spr[5].size = 1;

	// Pistol
	//dm->spr[6].pos.z = 3.0;
	//dm->spr[6].pos.y = 5.0;
	//dm->spr[6].pos.x = 7.5;
	dm->spr[6].pos.z = 8.0;
	dm->spr[6].pos.y = 4.5;
	dm->spr[6].pos.x = 20.5;
	dm->spr[6].gfx = 36;
	dm->spr[6].size = 1;

	//chest
	dm->spr[7].pos.z = 7.5;
	dm->spr[7].pos.y = 4.5;
	dm->spr[7].pos.x = 20.5;
	//printf("chest loc = %d  %d  %d\n", (int)(dm->spr[7].pos.z), (int)dm->spr[7].pos.y, (int)dm->spr[7].pos.x);
	dm->spr[7].gfx = 37;
	dm->spr[7].frame = 0;
	dm->spr[7].size = 3;
}






	/*//######### Chest ############
	i = 7;
	spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x) * 180 / M_PI + 180;
	dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
	dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
	dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
	dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
	if (spra < mina || spra > maxa)
		spra += 360;
	if (spra < mina || spra > maxa)
		spra -= 360;
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
	//chest width 197 height 197 per frame
	if (dm->chestopened)
		dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 196;
	else
		dm->gfx[dm->spr[i].gfx].x = 0;
	spra = atan2(dm->spr[i].dir.y * -1, dm->spr[i].dir.x * -1) * 180 / M_PI + 180;
	dm->spr[i].face.x = 1;
	sprb = atan2(dm->spr[i].face.y, dm->spr[i].face.x) * 180 / M_PI + 180;
	sprb = sprb - spra;
	if (sprb < 45 && sprb > -45)
		dm->gfx[dm->spr[i].gfx].y = 0;
	else if (sprb > 135 || sprb < -135)
		dm->gfx[dm->spr[i].gfx].y = 144;
	else if (sprb >= 45)
		dm->gfx[dm->spr[i].gfx].y = 48;
	else
		dm->gfx[dm->spr[i].gfx].y = 96;
	draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 197, 197, 0, 0, i}, 3 / dm->spr[i].dist);
	if (dm->chestopened && dm->spr[i].frame < 47)
		dm->spr[i].frame++;
	else if (dm->chestopened && dm->spr[i].frame == 47)
		dm->drawgunandkeycard = 1;
	*/



	/*//######### Pokemon trainer ############
	i = 8;
	spra = atan2(dm->spr[i].dir.y, dm->spr[i].dir.x) * 180 / M_PI + 180;
	dm->spr[i].dist = tri_pythagor(dm->pos, dm->spr[i].pos);
	dm->spr[i].dir.z = (dm->spr[i].pos.z - dm->pos.z) / dm->spr[i].dist;
	dm->spr[i].dir.y = (dm->spr[i].pos.y - dm->pos.y) / dm->spr[i].dist;
	dm->spr[i].dir.x = (dm->spr[i].pos.x - dm->pos.x) / dm->spr[i].dist;
	if (dm->spr[i].dist > 3)
	{
		dm->spr[i].pos.z += dm->spr[i].mov.z;
		dm->spr[i].pos.y += dm->spr[i].mov.y;
		dm->spr[i].pos.x += dm->spr[i].mov.x;
	}
	if (spra < mina || spra > maxa)
		spra += 360;
	if (spra < mina || spra > maxa)
		spra -= 360;
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

	//pokemon width 32 height 48 per frame
	dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 32;
	//printf("%dtraineranimation\n", dm->gfx[dm->spr[i].gfx].x);
	spra = atan2(dm->spr[i].dir.y * -1, dm->spr[i].dir.x * -1) * 180 / M_PI + 180;
	dm->spr[i].face.x = 1;
	sprb = atan2(dm->spr[i].face.y, dm->spr[i].face.x) * 180 / M_PI + 180;
	sprb = sprb - spra;
	//printf("%f trainer facing\n", sprb);
	if (sprb < 45 && sprb > -45)
		dm->gfx[dm->spr[i].gfx].y = 0;
	else if (sprb > 135 || sprb < -135)
		dm->gfx[dm->spr[i].gfx].y = 144;
	else if (sprb >= 45)
		dm->gfx[dm->spr[i].gfx].y = 48;
	else
		dm->gfx[dm->spr[i].gfx].y = 96;

	// "HASAM" (Highly Advanced Super Ai Movement)
	if (dm->spr[i].move == 'f')
	{
		if (dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x + 0.5)].b == 1 &&
			dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x + 0.05)].b == 1)
		{
			dm->spr[i].pos.x += 0.05;
			dm->spr[i].steps++;
			//printf("\n\nsteps f == %d\n\n", dm->spr[i].steps);
		}
		if (dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x + 0.5)].b != 1 ||
			dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x + 0.05)].b != 1)
		{
			//printf("\n\n\n\n\n\n\n---------\n\n\n\n\n\n\n");
			dm->spr[i].move = 'r';
			dm->spr[i].steps = 0;
		}
		if (dm->spr[i].steps == 50)
		{
			dm->spr[i].move = 'l';
			dm->spr[i].steps = 0;
		}
	}
	else if (dm->spr[i].move == 'r')
	{
		if (dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y + 0.5)][(int)dm->spr[i].pos.x].b == 1 &&
			dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y + 0.05)][(int)dm->spr[i].pos.x].b == 1)
		{
			dm->spr[i].pos.y += 0.05;
			dm->spr[i].steps++;
			//printf("\n\nsteps r == %d\n\n", dm->spr[i].steps);
		}
		else if (dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y + 0.5)][(int)dm->spr[i].pos.x].b != 1 ||
			dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y + 0.05)][(int)dm->spr[i].pos.x].b != 1)
		{
			dm->spr[i].move = 'b';
			dm->spr[i].steps = 0;
		}
		if (dm->spr[i].steps == 50)
		{
			dm->spr[i].move = 'f';
			dm->spr[i].steps = 0;
		}
	}
	else if (dm->spr[i].move == 'b')
	{
		if (dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x - 0.5)].b == 1 &&
			dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x - 0.05)].b == 1)
		{
			dm->spr[i].pos.x -= 0.05;
			dm->spr[i].steps++;
			//printf("\n\nsteps b == %d\n\n", dm->spr[i].steps);
		}
		else if (dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x - 0.5)].b != 1 ||
			dm->area[(int)dm->spr[i].pos.z][(int)dm->spr[i].pos.y][(int)(dm->spr[i].pos.x - 0.05)].b != 1)
		{
			dm->spr[i].move = 'l';
			dm->spr[i].steps = 0;
		}
		if (dm->spr[i].steps == 50)
		{
			dm->spr[i].move = 'r';
			dm->spr[i].steps = 0;
		}
	}
	else if (dm->spr[i].move == 'l')
	{
		if (dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y - 0.5)][(int)dm->spr[i].pos.x].b == 1 &&
			dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y - 0.05)][(int)dm->spr[i].pos.x].b == 1)
		{
			dm->spr[i].pos.y -= 0.05;
			dm->spr[i].steps++;
			//printf("\n\nsteps l == %d\n\n", dm->spr[i].steps);
		}
		else if (dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y - 0.5)][(int)dm->spr[i].pos.x].b != 1 ||
			dm->area[(int)(dm->spr[i].pos.z)][(int)(dm->spr[i].pos.y - 0.05)][(int)dm->spr[i].pos.x].b != 1)
		{
			dm->spr[i].move = 'f';
			dm->spr[i].steps = 0;
		}
		if (dm->spr[i].steps == 50)
		{
			dm->spr[i].move = 'b';
			dm->spr[i].steps = 0;
		}
	}
	//printf("dm->spr[i].pos.z == %f\n", dm->spr[i].pos.z);
	draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx], (int[7]){y, x, 48, 32, 0, 0, i}, 25 / dm->spr[i].dist);
	dm->spr[i].frame++;
	if (dm->spr[i].frame == 32)
		dm->spr[i].frame = 0;
	*/
