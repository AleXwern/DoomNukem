/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:24:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/17 15:59:48 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	part_dda_xn(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x >= DATA_BLK)
		dm->hit = 1;
	if (dm->rayd.x > 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_x(dm);
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 1 && dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] < 6)
			dm->hit = 1;
		if (dm->rmap2.x < DATA_BLK && dm->rmap2.x > 0)
			return;
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx * DATA_BLK;
		dm->side = 0;
		dm->hit = 1;
		dm->hithalf++;
	}
}

void	part_dda_xp(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x <= (1 - DATA_BLK))
		dm->hit = 1;
	if (dm->rayd.x < 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_x(dm);
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 1 && dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] < 6)
			dm->hit = 1;
		if (dm->rmap2.x > (1 - DATA_BLK) && dm->rmap2.x < LIM)
			return;
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx * DATA_BLK;
		dm->side = 0;
		dm->hit = 1;
		dm->hithalf++;
		dm->texshift.x = 1;
	}
}