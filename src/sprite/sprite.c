/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:24:25 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/28 14:43:46 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	Keycard 30 --
**	Jetpack 9 --
**	Money 34 --
**	Plant 35 --
**	Pistol 36 --
**	Chest 37 --
*/

void	pickupitem(t_doom *dm)
{
	int	i;

	i = -1;
	while (++i < OBJ)
	{
		if (dm->obj[i].gfx == 35 || dm->obj[i].dist >= 2.5 ||
			dm->obj[i].dead)
			continue;
		else if (dm->obj[i].gfx == 37 && dm->obj[i].dist < 2.5)
			dm->chestopened = 1;
		else if (dm->obj[i].dist < 1.5)
		{
			if (dm->obj[i].gfx == 36 && dm->drawgunandkeycard)
				dm->gun = 1;
			else if (dm->obj[i].gfx == 34)
				dm->money++;
			else if (dm->obj[i].gfx == 30 && dm->drawgunandkeycard)
				dm->keycard = 1;
			else if (dm->obj[i].gfx == 9)
				dm->jetpack = 1;
			dm->obj[i].dead = 1;
		}
	}
}
