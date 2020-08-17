/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:56:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/17 15:01:43 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	single_loop_z(t_doom* dm)
{
	dm->tmap = dm->map;
	dm->tsided = dm->sided;
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
	{
		dm->tsided.x += dm->deltad.x;
		dm->tmap.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
	{
		dm->tsided.y += dm->deltad.y;
		dm->tmap.y += dm->stepy;
		dm->side = 1;
	}
	else
	{
		dm->tsided.z += dm->deltad.z;
		dm->tmap.z += dm->stepz;
		dm->side = 2;
	}
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.z = dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->tmap.z;
}

void	single_loop_y(t_doom* dm)
{
	dm->tmap = dm->map;
	dm->tsided = dm->sided;
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
	{
		dm->tsided.x += dm->deltad.x;
		dm->tmap.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
	{
		dm->tsided.y += dm->deltad.y;
		dm->tmap.y += dm->stepy;
		dm->side = 1;
	}
	else
	{
		dm->tsided.z += dm->deltad.z;
		dm->tmap.z += dm->stepz;
		dm->side = 2;
	}
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
}

void	single_loop_x(t_doom* dm)
{
	dm->tmap = dm->map;
	dm->tsided = dm->sided;
	if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
	{
		dm->tsided.x += dm->deltad.x;
		dm->tmap.x += dm->stepx;
		dm->side = 0;
	}
	else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
	{
		dm->tsided.y += dm->deltad.y;
		dm->tmap.y += dm->stepy;
		dm->side = 1;
	}
	else
	{
		dm->tsided.z += dm->deltad.z;
		dm->tmap.z += dm->stepz;
		dm->side = 2;
	}
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->tmap.x;
}
