/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:54:01 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/14 14:03:52 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	Chest
**	Pistol
**	Keycard
*/

void	obj_set(t_doom *dm, int i)
{
	dm->obj[i].pos.z = 7.5;
	dm->obj[i].pos.y = 4.5;
	dm->obj[i].pos.x = 20.5;
	dm->obj[i].gfx = 37;
	dm->obj[i].frame = 0;
	dm->obj[i++].size = 17;
	dm->obj[i].pos.z = 8.0;
	dm->obj[i].pos.y = 4.5;
	dm->obj[i].pos.x = 20.5;
	dm->obj[i].gfx = 36;
	dm->obj[i++].size = 1;
	dm->obj[i].pos.z = 8.0;
	dm->obj[i].pos.y = 2.8;
	dm->obj[i].pos.x = 20.5;
	dm->obj[i].gfx = 30;
	dm->obj[i].size = 1;
}

/*
**	Aggron i = 7
**	Woman i = 8
*/

void	sprite_set2(t_doom *dm, int i, int sprite)
{
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 12.4;
	dm->spr[i++].pos.x = 17.4;
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 12.4;
	dm->spr[i].pos.x = 20.4;
	while (i > 3)
	{
		dm->spr[i].hp = 2;
		dm->spr[i].gfx = sprite--;
		dm->spr[i--].size = 25;
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
	dm->spr[i].pos.y = 12.4;
	dm->spr[i++].pos.x = 8.4;
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 12.4;
	dm->spr[i++].pos.x = 11.4;
	dm->spr[i].pos.z = 7.4;
	dm->spr[i].pos.y = 12.4;
	dm->spr[i++].pos.x = 14.4;
	sprite_set2(dm, i, 20);
}
