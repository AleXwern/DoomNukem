/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:54:01 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 14:26:15 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	Money 8
**	Money 9
**	Money 10
**	Money 11
*/

void	obj_set3(t_doom *dm, int i)
{
	dm->obj[i].pos.z = 2.0;
	dm->obj[i].pos.y = 3.5;
	dm->obj[i].pos.x = 13.5;
	dm->obj[i].gfx = 34;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 2.0;
	dm->obj[i].pos.y = 8.5;
	dm->obj[i].pos.x = 18.5;
	dm->obj[i].gfx = 34;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 4.0;
	dm->obj[i].pos.y = 3.8;
	dm->obj[i].pos.x = 23.0;
	dm->obj[i].gfx = 34;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 8.0;
	dm->obj[i].pos.y = 8.5;
	dm->obj[i].pos.x = 10.5;
	dm->obj[i].gfx = 34;
	dm->obj[i++].size = 1;
}

/*
**	Plant 4
**	Plant 5
**	Plant 6
**	Plant 7
*/

void	obj_set2(t_doom *dm, int i)
{
	dm->obj[i].pos.z = 3.6;
	dm->obj[i].pos.y = 15.0;
	dm->obj[i].pos.x = 22.5;
	dm->obj[i].gfx = 35;
	dm->obj[i++].size = 2;
	dm->obj[i].pos.z = 4.6;
	dm->obj[i].pos.y = 23.0;
	dm->obj[i].pos.x = 4.6;
	dm->obj[i].gfx = 35;
	dm->obj[i++].size = 2;
	dm->obj[i].pos.z = 6.2;
	dm->obj[i].pos.y = 3.6;
	dm->obj[i].pos.x = 21.0;
	dm->obj[i].gfx = 35;
	dm->obj[i++].size = 3;
	dm->obj[i].pos.z = 7.6;
	dm->obj[i].pos.y = 19.0;
	dm->obj[i].pos.x = 5.1;
	dm->obj[i].gfx = 35;
	dm->obj[i++].size = 2;
	obj_set3(dm, i);
}

/*
**	Chest 0
**	Pistol 1
**	Keycard 2
**	Plant 3
*/

void	obj_set(t_doom *dm, int i)
{
	dm->obj[i].pos.z = 3.5;
	dm->obj[i].pos.y = 3.1;
	dm->obj[i].pos.x = 17.5;
	dm->obj[i].gfx = 37;
	dm->obj[i].frame = 0;
	dm->obj[i++].size = 17;
	dm->obj[i].pos.z = 4.0;
	dm->obj[i].pos.y = 3.3;
	dm->obj[i].pos.x = 17.5;
	dm->obj[i].gfx = 36;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 3.8;
	dm->obj[i].pos.y = 4.0;
	dm->obj[i].pos.x = 17.5;
	dm->obj[i].gfx = 30;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 1.6;
	dm->obj[i].pos.y = 10.0;
	dm->obj[i].pos.x = 2.0;
	dm->obj[i].gfx = 35;
	dm->obj[i++].size = 2;
	obj_set2(dm, i);
}

/*
**	Aggron i = 7
**	Woman i = 8
*/

void	sprite_set2(t_doom *dm, int i, int sprite)
{
	dm->spr[i].pos.z = 6.4;
	dm->spr[i].pos.y = 10.4;
	dm->spr[i++].pos.x = 17.4;
	dm->spr[i].pos.z = 6.4;
	dm->spr[i].pos.y = 9.4;
	dm->spr[i].pos.x = 16.4;
	while (i > 3)
	{
		dm->spr[i].hp = 2;
		dm->spr[i].gfx = sprite--;
		dm->spr[i--].size = 15;
	}
	obj_set(dm, 0);
}

/*
**	Charizard i = 4
**	PokemonTrainer i = 5
**	Dragon i = 6
*/

void	sprite_set(t_doom *dm, int i)
{
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 13.4;
	dm->spr[i++].pos.x = 4.5;
	dm->spr[i].pos.z = 4.4;
	dm->spr[i].pos.y = 20.7;
	dm->spr[i++].pos.x = 3.2;
	dm->spr[i].pos.z = 6.4;
	dm->spr[i].pos.y = 4.4;
	dm->spr[i++].pos.x = 6.4;
	sprite_set2(dm, i, 20);
}
