/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:56:57 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/16 15:03:07 by anystrom         ###   ########.fr       */
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

void	init_functions(void (*block[10])(t_doom*, double), void (*slope[12])(t_doom*, int))
{
	ft_putendl("init funct");
	block[0] = part_dda_zp;
	block[1] = part_dda_zn;
	block[2] = part_dda_yp;
	block[3] = part_dda_yn;
	block[4] = part_dda_xp;
	block[5] = part_dda_xn;
	slope[0] = slope_dda_yzt;
	slope[1] = slope_dda_yzb;
	slope[2] = slope_dda_yztr;
	slope[3] = slope_dda_yzbr;
	slope[4] = slope_dda_xzt;
	slope[5] = slope_dda_xzb;
	slope[6] = slope_dda_xztr;
	slope[7] = slope_dda_xzbr;
	slope[8] = slope_dda_xyt;
	slope[9] = slope_dda_xyb;
	slope[10] = slope_dda_xytr;
	slope[11] = slope_dda_xybr;
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
	double		plane;
	int			pt;
	static void	(*block[6])(t_doom*, double);
	static void	(*slope[12])(t_doom*, int);

	if (block[0] == NULL)
		init_functions(block, slope);
	plane = (1 - dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pln / 15.0);
	pt = dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pt - 1;
	if (pt >= 6)
		slope[pt - 6](dm, dm->side);
	else
		block[pt](dm, plane);
}
