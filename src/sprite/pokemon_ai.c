/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon_ai.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:28:29 by tbergkul          #+#    #+#             */
/*   Updated: 2020/09/30 16:44:16 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	ai_movement(t_doom *dm, t_sprite *s)
{
	// "HASA" (Highly Advanced Super Ai)
	if (s->move == 'a')//alerted
	{
		if (dm->gfx[s->gfx].y == 37 || dm->gfx[s->gfx].y == 74)
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

void	pokemon_trainer_dir(t_doom *dm, int i)
{
	double	spra;
	double	sprb;

	if (dm->spr[i].move != 'x')
		dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame / 8) * 28;
	else
		dm->gfx[dm->spr[i].gfx].x = (dm->spr[i].frame < 16 ? 0 : 56);
	dm->spr[i].face = dm->spr[i].dir;////
	if (dm->spr[i].move == 'x')
	{
		spra = atan2(dm->spr[i].face.y, dm->spr[i].face.x) * 180 / M_PI + 180;
		sprb = atan2(0, 1) * 180 / M_PI + 180;
		sprb = sprb - spra;
		if (sprb < 45 && sprb > -45)
			dm->gfx[dm->spr[i].gfx].y = 0;
		else if (sprb > 135 || sprb < -135)
			dm->gfx[dm->spr[i].gfx].y = 111;
		else if (sprb >= 45)
			dm->gfx[dm->spr[i].gfx].y = 37;
		else
			dm->gfx[dm->spr[i].gfx].y = 74;
	}
}

/*
**	Pokemon width 32, height 48 per frame
*/

void	pokemon_trainer_mode(t_doom *dm, int i)
{
	pokemon_trainer_dir(dm, i);
	if (dm->spr[i].dist <= 7 && dm->spr[i].dist >= 6.5)
	{
		if (dm->gfx[dm->spr[i].gfx].y != 111 && dm->spr[i].move != 'm'/* && you can see the sprite*/)
			dm->spr[i].move = 'a';//alerted
		dm->spr[i].mov.x = dm->spr[i].dir.x * -0.03;
		dm->spr[i].mov.y = dm->spr[i].dir.y * -0.03;
	}
	else if (dm->spr[i].dist <= 6.5 /* && you can see the sprite*/)
	{
		dm->spr[i].move = 's';//shooting
		// if (i == 6)
		// 	dm->gfx[dm->spr[i].gfx].x = 28;//charizard
		// else
		dm->gfx[dm->spr[i].gfx].x = 0;
		dm->gfx[dm->spr[i].gfx].y = 0;
	}
	else
		dm->spr[i].move = 'x';//stand still
}


void	pokemon_trainer(t_doom *dm, int y, int x, int i)
{
	pokemon_trainer_mode(dm, i);
	ai_movement(dm, &dm->spr[i]);
	draw_sprite_gfx(dm, dm->gfx[dm->spr[i].gfx],
		(int[7]){y, x, 37, 28, 0, 0, i}, 25 / dm->spr[i].dist);
	dm->spr[i].frame++;
	if (dm->spr[i].frame == 32)
		dm->spr[i].frame = 0;
}
