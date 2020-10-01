/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:54:01 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/01 13:13:31 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	sprite_set2(t_doom *dm)
{
	int	i;
	// PokemonTrainer
	dm->spr[5].hp = 2;
	dm->spr[5].pos.z = 7.4;
	dm->spr[5].pos.y = 12.4;
	dm->spr[5].pos.x = 16.4;
	dm->spr[5].gfx = 22;
	dm->spr[5].move = 'x';
	dm->spr[5].frame = 0;
	dm->spr[5].size = 25;
	dm->spr[5].face.x = 0;//use this as a "which direction is the trainer facing"//not in use at the moment

	// Charizard
	dm->spr[6].hp = 2;
	dm->spr[6].pos.z = 7.4;
	dm->spr[6].pos.y = 12.4;
	dm->spr[6].pos.x = 5.4;
	dm->spr[6].gfx = 16;
	dm->spr[6].move = 'x';
	dm->spr[6].frame = 0;
	dm->spr[6].size = 25;

	i = 7;
	dm->spr[i].hp = 2;
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 14.4;
	dm->spr[i].pos.x = 12.4;
	dm->spr[i].gfx = 18;//dragon
	dm->spr[i].size = 25;
	dm->spr[i].move = 'x';
	i++;
	dm->spr[i].hp = 2;
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 3.4;
	dm->spr[i].pos.x = 5.4;
	dm->spr[i].gfx = 21;//aggron
	dm->spr[i].size = 25;
	dm->spr[i].move = 'x';

	//chest
	dm->obj[0].pos.z = 7.5;
	dm->obj[0].pos.y = 4.5;
	dm->obj[0].pos.x = 20.5;
	dm->obj[0].gfx = 37;
	dm->obj[0].frame = 0;
	dm->obj[0].size = 3;
	//printf("chest loc = %d  %d  %d\n", (int)(dm->obj[7].pos.z), (int)dm->obj[7].pos.y, (int)dm->obj[7].pos.x);

	// Pistol
	//dm->obj[1].pos.z = 3.0;
	//dm->obj[1].pos.y = 5.0;
	//dm->obj[1].pos.x = 7.5;
	dm->obj[1].pos.z = 8.0;
	dm->obj[1].pos.y = 4.5;
	dm->obj[1].pos.x = 20.5;
	dm->obj[1].gfx = 36;
	dm->obj[1].size = 1;

	// Keycard
	//dm->obj[2].pos.z = 3.0;
	//dm->obj[2].pos.y = 6.0;
	//dm->obj[2].pos.x = 7.5;
	dm->obj[2].pos.z = 8.0;
	dm->obj[2].pos.y = 2.8;
	dm->obj[2].pos.x = 20.5;
	dm->obj[2].gfx = 30;
	dm->obj[2].size = 1;
}

void	sprite_set(t_doom *dm)
{
	int	i;
	//static int	i;

	// if (i)
	// 	return;
	i = 3;
	while (++i < 5)
	{
		dm->spr[i].hp = 1 * (i + 1);
		dm->spr[i].pos.z = 7.4;//(rand() % 90) / 10;
		dm->spr[i].pos.y = (rand() % (25 - 1 + 1)) + 1;//(rand() % 250) / 10;
		dm->spr[i].pos.x = (rand() % (25 - 1 + 1)) + 1;//(rand() % 250) / 10;
		dm->spr[i].gfx = (rand() % (23 - 16 + 1)) + 16;//(rand() % 7) + 16;
		//printf("y %f  x %f   gfx %d\n", dm->spr[i].pos.y, dm->spr[i].pos.x, dm->spr[i].gfx);
		dm->spr[i].size = 25;
		dm->spr[i].move = 's';//so that all sprites will shoot
	}
	sprite_set2(dm);
}
