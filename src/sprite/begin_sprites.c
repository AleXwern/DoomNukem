/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:54:01 by tbergkul          #+#    #+#             */
/*   Updated: 2020/09/24 14:19:27 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	sprite_set2(t_doom *dm)
{
	// PokemonTrainer
	dm->spr[5].hp = 2;
	dm->spr[5].pos.z = 6.6;
	dm->spr[5].pos.y = 12.4;
	dm->spr[5].pos.x = 16.4;
	dm->spr[5].gfx = 32;
	dm->spr[5].move = 'x';
	dm->spr[5].frame = 0;
	//dm->spr[5].size = 5;
	dm->spr[5].face.x = 0;//use this as a "which direction is the trainer facing"//not in use at the moment

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
	static int	i;
	double		mov;

	mov = dm->movsp * ((30.0 / dm->buffer) / dm->prefps);
	if (mov > 1.0 || mov < -1.0)
		mov /= fabs(mov) * 2;

	if (i)
		return;
	dm->spr[0].hp = 2;
	dm->spr[0].pos.z = 7.2;
	dm->spr[0].pos.y = 12.42;
	dm->spr[0].pos.x = 12.4;
	dm->spr[0].gfx = 34;
	dm->spr[0].size = 1;
	while (++i < 4)
	{
		dm->spr[i].hp = 1 * (i + 1);
		dm->spr[i].pos.z = (rand() % 90) / 10;
		dm->spr[i].pos.y = (rand() % 250) / 10;
		dm->spr[i].pos.x = (rand() % 250) / 10;
		dm->spr[i].gfx = (rand() % 8) + 15;
		dm->spr[i].size = 1;
		dm->spr[i].move = 's';//so that all sprites will shoot
	}
	sprite_set2(dm);
}
