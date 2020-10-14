/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_passive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:11:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/14 14:09:42 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*
**	's' -shooting
**	'a' -alerted
**	Passive
**	'x' -stand still
**	'm' -moving
**	printf("%d Cycle %d of %d type %c\n", i, frm[i], cycle[i], spr->move);
*/

void	foe_passive_cycle(t_doom *dm, t_sprite *spr, int i)
{
	static int	cycle[5];
	static int	frm[5];

	if (spr->move != 'm' && spr->move != 'x')
	{
		cycle[i] = 0;
		return ;
	}
	dm->rng += (spr->pos.z + spr->pos.y + spr->pos.x) * M_PI;
	if (++frm[i] >= cycle[i])
	{
		frm[i] = 0;
		cycle[i] = dm->rng % 400 + 70;
	}
	if (frm[i])
		return ;
	if (dm->rng % 100 > 77)
		spr->mov = (t_vector){.z = 0, .y = 0, .x = 0};
	else if (dm->rng % 100 > 90)
		spr->mov = (t_vector){.y = spr->dir.y * 0.03, .x = spr->dir.x * 0.03 };
	else
		spr->mov = (t_vector){.y = ((dm->rng % 213 - 106) / 106.0) * 0.03,
							.x = ((dm->rng % 97 - 48) / 48.0) * 0.03 };
	spr->face = spr->mov;
}
