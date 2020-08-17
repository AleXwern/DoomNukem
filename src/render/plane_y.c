/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:24:09 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/17 15:59:28 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	part_dda_yn(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y >= DATA_BLK)
		dm->hit = 1;
	if (dm->rayd.y > 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 1 && dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] < 6)
			dm->hit = 1;
		if (dm->rmap2.y < DATA_BLK && dm->rmap2.y > 0)
			return;
		dm->sided.y += dm->deltad.y;
		dm->map.y += dm->stepy * DATA_BLK;
		dm->side = 1;
		dm->hit = 1;
		dm->hithalf++;
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] == 6)
			part_dda_yn(dm);
	}
}

void	part_dda_yp(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y <= (1 - DATA_BLK))
		dm->hit = 1;
	if (dm->rayd.y < 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] > 1 && dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] < 6)
			dm->hit = 1;
		if (dm->rmap2.y > (1 - DATA_BLK) && dm->rmap2.y < 1)
			return;
		dm->sided.y += dm->deltad.y;
		dm->map.y += dm->stepy * DATA_BLK;
		dm->side = 1;
		dm->hit = 1;
		dm->hithalf++;
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x] == 6)
			part_dda_yp(dm);
		dm->texshift.y = 1;
	}
}
