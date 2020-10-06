/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_ai.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:50:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/02 13:34:33 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	's' -shooting
**	'a' -alerted
**	Passive
**	'x' -stand still/passive
**	'm' -moving
*/

void	foe_dir(t_doom *dm, t_sprite *spr, double spra)
{
	if (!foe_ismoving(spr))
		dm->gfx[spr->gfx].x = (spr->frame / 8) * 28;
	else
		dm->gfx[spr->gfx].x = (spr->frame < 16 ? 0 : 56);
	spra = (atan2(spr->dir.y, spr->dir.x) - atan2(spr->face.y, spr->face.x))
		* 180 / M_PI;
	//spra = spra - spra;
	if (spra >= 180)
		spra -= 360;
	else if (spra <= -180)
		spra += 360;
	if (spra < 45 && spra > -45)
		dm->gfx[spr->gfx].y = BACKS;
	else if (spra > 135 || spra < -135)
		dm->gfx[spr->gfx].y = FRONTS;
	else if (spra >= 45)
		dm->gfx[spr->gfx].y = LEFTS;
	else
		dm->gfx[spr->gfx].y = RIGHTS;
}

void	foe_mode(t_doom *dm, t_sprite *spr)
{
	if ((spr->dist <= 8 && dm->gfx[spr->gfx].y != BACKS) ||
		spr->dist <= 5)
	{
		spr->face = (t_vector){ .y = spr->dir.y * -1,
			.x = spr->dir.x * -1 };
		spr->move = 'a';
	}
	if (spr->dist <= 8 && spr->dist >= 3.5 && (spr->move == 'a' || spr->move == 's'))
	{
		spr->mov.x = spr->dir.x * -0.03;
		spr->mov.y = spr->dir.y * -0.03;
	}
}

void	foe_shooting(t_doom *dm, t_sprite *spr, t_sprite *prj)
{
	if (spr->move == 's')
	{
		prj->mov = (t_vector){.z = spr->dir.z * -0.2,
			.y = spr->dir.y * -0.2, .x = spr->dir.x * -0.2};
		prj->pos.z = spr->pos.z + (prj->mov.z * 2);
		prj->pos.y = spr->pos.y + (prj->mov.y * 2);
		prj->pos.x = spr->pos.x + (prj->mov.x * 2);
		prj->move == 'm';
	}
	if (prj->move == 'm')
	{
		prj->pos.z += prj->mov.z;
		prj->pos.y += prj->mov.y;
		prj->pos.x += prj->mov.x;
	}
	if (prj->move == 'm' && prj->dist < 0.6)
	{
		if (!dm->iframe && dm->invincible != 4)
		{
			dm->hp -= 1;
			dm->iframe = 50;
		}
		ft_bzero(prj, sizeof(t_sprite));
	}
	if (prj->move == 'm' && dm->area[(int)prj->pos.z][(int)prj->pos.y][(int)prj->pos.x].b > 1)
		ft_bzero(prj, sizeof(t_sprite));
}

void	foe_collision(t_doom* dm, t_sprite* spr, int i, int s)
{
	t_vector	npos;
	double		dist;

	npos = spr->pos;
	while (++i < 9)
	{
		dist = tri_pythagor(spr->pos, dm->spr[i].pos);
		if (dist < 1.2 && fabs(spr->pos.z - dm->spr[i].pos.z) < 1.3 && i != s)
		{
			npos.x -= spr->mov.x;
			npos.y -= spr->mov.y;
			if (dm->area[(int)npos.z][(int)spr->pos.y][(int)npos.x].b <= 1)
				spr->pos.x = npos.x;
			if (dm->area[(int)npos.z][(int)npos.y][(int)spr->pos.x].b <= 1)
				spr->pos.y = npos.y;
		}
	}
}

void	foe_move(t_doom *dm, t_sprite *spr)
{
	t_vector	mov;

	ft_bzero(&mov, sizeof(t_vector));
	if (dm->area[(int)spr->pos.z][(int)spr->pos.y][(int)(spr->pos.x + spr->mov.x)].b <= 1)
		mov.x += spr->mov.x;
	if (dm->area[(int)spr->pos.z][(int)(spr->pos.y + spr->mov.y)][(int)spr->pos.x].b <= 1)
		mov.y += spr->mov.y;
	spr->face = mov;
	spr->pos.x += mov.x;
	spr->pos.y += mov.y;
}

void	foe_ai(t_doom *dm, t_sprite *spr, int *yx, int i)
{
	foe_dir(dm, spr, 0);
	foe_mode(dm, spr);
	foe_passive_cycle(dm, spr, i);
	spr->frame++;
	if (spr->move != 'x' && spr->move != 'm')
	{
		//if (spr->frame >= 36 && spr->dist < 4)
		//	spr->frame = 0;
		if (spr->frame >= 32 && spr->dist < 8)
			spr->frame = 0;
		if (spr->frame == 0)
			spr->move = 's';
	}
	else if (spr->frame >= 32)
		spr->frame = 0;
	foe_shooting(dm, spr, &dm->prj[i], i);
	foe_move(dm, spr);
	foe_collision(dm, spr, -1, i);
	draw_sprite_gfx(dm, dm->gfx[spr->gfx],
		(int[7]) {yx[0], yx[1], 37, 28, 0, 0, i}, spr->size / spr->dist);
}
