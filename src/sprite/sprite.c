/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:04:11 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/06 19:04:11 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**keycard
**pistol
**chest
*/

void	pickupitem(t_doom* dm)
{
	if (dm->obj[2].dist < 1.5)
	{
		dm->keycard = 1;
		ft_bzero(&dm->obj[2], sizeof(t_sprite));
	}
	else if (dm->obj[1].dist < 1.5)
	{
		dm->gun = 1;
		ft_bzero(&dm->obj[1], sizeof(t_sprite));
	}
	else if (dm->obj[0].dist < 2.5 && !dm->chestopened)
		dm->chestopened = 1;
}

/*
**chest width 197 height 197 per frame
*/

void	chest_object(t_doom *dm, int i, int y, int x)
{
	if (dm->chestopened)
		dm->gfx[dm->obj[i].gfx].x = (dm->obj[i].frame / 8) * 196;
	else
		dm->gfx[dm->obj[i].gfx].x = 0;
	draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx],
		(int[7]){y, x, 197, 197, 0, 0, i}, 3 / dm->obj[i].dist);
	if (dm->chestopened && dm->obj[i].frame < 47)
		dm->obj[i].frame++;
	else if (dm->chestopened && dm->obj[i].frame == 47)
		dm->drawgunandkeycard = 1;
}
