/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:01:50 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/19 14:41:21 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	get_ppos(t_doom *dm, t_block blk)
{
	if (blk.pt == 0)
		return;
	else if (dm->rayd.z < 0 && blk.pt == 2)
		dm->adj = 1;
	else if (dm->rayd.z > 0 && blk.pt == 1)
		dm->adj = 1;
	else if (dm->rayd.y > 0 && blk.pt == 3)
		dm->adj = 1;
	else if (dm->rayd.y < 0 && blk.pt == 4)
		dm->adj = 1;
	else if (dm->rayd.x > 0 && blk.pt == 5)
		dm->adj = 1;
	else if (dm->rayd.x < 0 && blk.pt == 6)
		dm->adj = 1;
}

void	dda_sys2(t_doom *dm)
{
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z && !dm->hit)
	{
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z && !dm->hit)
	{
		dm->sided.y += dm->deltad.y;
		dm->map.y += dm->stepy;
		dm->side = 1;
	}
	else if (!dm->hit)
	{
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz;
		dm->side = 2;
	}
	dm->adj = 0;
}

void	dda_sys(t_doom *dm)
{
	dm->hit = 0;
	dm->adj = 0;
	get_ppos(dm, dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x]);
	while (dm->hit == 0)
	{
		if (dm->map.z < 0 || dm->map.y < 0 || dm->map.x < 0
			|| dm->map.z >= 9 || dm->map.y >= 25 || dm->map.x >= 25)
		{
			dm->hit = 2;
			return ;
		}
		dm->blk = dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x];
		if (dm->blk.pt && !dm->adj && dm->blk.b > 1)
			part_check(dm);
		//else if (dm->blk.b > 6 && !dm->adj) 								//FS should handle these
		//	dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b = 1;
		else if (dm->blk.b > 1 && !dm->adj)
			dm->hit = 1;
		dda_sys2(dm);
	}
}

void	dda_prep2(t_doom *dm)
{
	if (dm->rayd.z < 0)
	{
		dm->stepz = -1;
		dm->sided.z = (dm->pos.z - dm->map.z) * dm->deltad.z;
	}
	else
	{
		dm->stepz = 1;
		dm->sided.z = (dm->map.z + 1.0 - dm->pos.z) * dm->deltad.z;
	}
}

void	dda_prep(t_doom *dm)
{
	dm->deltad.x = fabs(1 / dm->rayd.x);
	dm->deltad.y = fabs(1 / dm->rayd.y);
	dm->deltad.z = fabs(1 / dm->rayd.z);
	if (dm->rayd.x < 0)
	{
		dm->stepx = -1;
		dm->sided.x = (dm->pos.x - dm->map.x) * dm->deltad.x;
	}
	else
	{
		dm->stepx = 1;
		dm->sided.x = (dm->map.x + 1.0 - dm->pos.x) * dm->deltad.x;
	}
	if (dm->rayd.y < 0)
	{
		dm->stepy = -1;
		dm->sided.y = (dm->pos.y - dm->map.y) * dm->deltad.y;
	}
	else
	{
		dm->stepy = 1;
		dm->sided.y = (dm->map.y + 1.0 - dm->pos.y) * dm->deltad.y;
	}
	dda_prep2(dm);
}
