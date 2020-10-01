/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe_passive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:11:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/01 14:29:09 by anystrom         ###   ########.fr       */
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
*/

void	foe_passive_cycle(t_doom *dm, t_sprite *spr)
{
	static int	cycle;
	static int	frm;

	if (spr->move != 'x' && spr->move != 'm')
	{
		cycle = 0;
		return ;
	}
	if (frm >= cycle)
	{
		frm = 0;
		cycle = dm->rng % 400 + 70;
	}
	if (!frm)
		return;
	if (dm->rng % 100 > 77)
		spr->mov = (t_vector){.z = 0, .y = 0, .x = 0};
	else if (dm->rng % 100 > 90)
		spr->mov = (t_vector){.y = spr->dir.y * -0.03, .x = spr->dir.x * -0.03};
	else
		spr->mov = (t_vector){.y = dm->rng % 3 - 1, .x = dm->rng % 3 - 1};
	frm++;
}