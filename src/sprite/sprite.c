/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:24:25 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/15 14:09:49 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	pickupitem2(t_doom *dm)
{
	if (dm->obj[7].dist < 1.5)
	{
		dm->money++;
		ft_bzero(&dm->obj[7], sizeof(t_sprite));
	}
	else if (dm->obj[8].dist < 1.5)
	{
		dm->money++;
		ft_bzero(&dm->obj[8], sizeof(t_sprite));
	}
}

/*
**	chest
**	pistol
**	keycard
**	money
**	money
*/

void	pickupitem(t_doom *dm)
{
	if (dm->obj[0].dist < 2.5 && !dm->chestopened)
		dm->chestopened = 1;
	else if (dm->obj[1].dist < 1.5)
	{
		dm->gun = 1;
		ft_bzero(&dm->obj[1], sizeof(t_sprite));
	}
	else if (dm->obj[2].dist < 1.5)
	{
		dm->keycard = 1;
		ft_bzero(&dm->obj[2], sizeof(t_sprite));
	}
	else if (dm->obj[5].dist < 1.5)
	{
		dm->money++;
		ft_bzero(&dm->obj[5], sizeof(t_sprite));
	}
	else if (dm->obj[6].dist < 1.5)
	{
		dm->money++;
		ft_bzero(&dm->obj[6], sizeof(t_sprite));
	}
	pickupitem2(dm);
}

/*
**	chest width 197 height 197 per frame
*/

void	draw_object(t_doom *dm, int i, int y, int x)
{
	if (i == 0)
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
	else
		draw_object_gfx(dm, dm->gfx[dm->obj[i].gfx],
		(int[7]){y, x, dm->gfx[dm->obj[i].gfx].hgt,
		dm->gfx[dm->obj[i].gfx].wid, 0, 0, i},
		dm->obj[i].size / dm->obj[i].dist);
}
