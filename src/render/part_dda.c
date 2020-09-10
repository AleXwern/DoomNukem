/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:56:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/04 13:23:54 by anystrom         ###   ########.fr       */
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

/*
**	PLANE TYPE
**	0 - none
**	1 - Z, filled up
**	2 - Z, filled down
**	3 - Y, filled N
**	4 - Y, filled S
**	5 - X, filled W
**	6 - X, filled E
*/
void	part_check(t_doom *dm)
{
	double	plane;
	int		pt;

	plane = (1 - dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pln / 15.0);
	pt = dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pt;
	if (pt == 1)
		part_dda_zp(dm, plane);
	else if (pt == 2)
		part_dda_zn(dm, plane);
	else if (pt == 3)
		part_dda_yp(dm, plane);
	else if (pt == 4)
		part_dda_yn(dm, plane);
	else if (pt == 5)
		part_dda_xp(dm, plane);
	else if (pt == 6)
		part_dda_xn(dm, plane);
	else if (pt == 7)
		slope_dda_xzn(dm);
	else
		slope_dda_xzp(dm);
}
