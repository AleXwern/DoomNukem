/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_ai.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:50:55 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/14 14:09:30 by tbergkul         ###   ########.fr       */
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

void	foe_collision(t_doom *dm, t_sprite *spr, int i, int s)
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

void	foe_dir(t_doom *dm, t_sprite *spr, double spra)
{
	if (foe_ismoving(spr))
		dm->gfx[spr->gfx].x = (spr->frame / 8) * 28;
	else
		dm->gfx[spr->gfx].x = (spr->frame < 16 ? 0 : 56);
	spra = (atan2(spr->dir.y, spr->dir.x) - atan2(spr->face.y, spr->face.x))
		* 180 / M_PI;
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
	if (((spr->dist <= 8 && dm->gfx[spr->gfx].y != BACKS) ||
		spr->dist <= 5) && fabs(dm->pos.z - spr->pos.z) <= 4)
	{
		spr->face = (t_vector){ .y = spr->dir.y * -1,
			.x = spr->dir.x * -1 };
		spr->move = 'a';
	}
	if (spr->dist <= 8 && spr->dist >= 3.5
		&& (spr->move == 'a' || spr->move == 's'))
	{
		spr->mov.x = spr->dir.x * -0.03;
		spr->mov.y = spr->dir.y * -0.03;
	}
}

void	foe_move(t_doom *dm, t_sprite *spr)
{
	t_vector	mov;

	ft_bzero(&mov, sizeof(t_vector));
	if (dm->area[(int)spr->pos.z][(int)spr->pos.y]
		[(int)(spr->pos.x + spr->mov.x)].b <= 1)
		mov.x += spr->mov.x;
	if (dm->area[(int)spr->pos.z][(int)(spr->pos.y + spr->mov.y)]
		[(int)spr->pos.x].b <= 1)
		mov.y += spr->mov.y;
	spr->face = mov;
	spr->pos.x += mov.x;
	spr->pos.y += mov.y;
}

void	foe_ai(t_doom *dm, t_sprite *spr, int *yx, int i)
{
	double	dist;

	foe_dir(dm, spr, 0);
	foe_mode(dm, spr);
	foe_passive_cycle(dm, spr, i - 4);
	spr->frame++;
	if (spr->frame >= 32)
		spr->frame = 0;
	if (spr->move == 'a' && spr->frame == 0)
		spr->move = 's';
	foe_move(dm, spr);
	foe_collision(dm, spr, -1, i);
	dist = spr->dist * (1.0 - ((fabs(dm->winw / 2.0) / (dm->winw / 2)) / 6));
	draw_sprite_gfx(dm, dm->gfx[spr->gfx],
		(int[7]){yx[0], yx[1], 37, 28, 0, 0, i}, spr->size / dist);
}
