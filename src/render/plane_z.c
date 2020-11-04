/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_z.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 13:21:59 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/30 14:42:56 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	part_dda_zn(t_doom *dm, double plane)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5)
			/ dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5)
			/ dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5)
			/ dm->rayd.z;
	if (dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z >= plane)
		dm->hit = 1;
	if (dm->rayd.z > 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		if (dm->rmap2.z < plane && dm->rmap2.z > 0)
			return ;
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz * plane;
		dm->side = 2;
		dm->hit = 1;
	}
}

void	part_dda_zp_more(t_doom *dm, double plane)
{
	if (dm->rayd.z < 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		if (dm->rmap2.z > (1 - plane) && dm->rmap2.z < LIM)
			return ;
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz * plane;
		dm->side = 2;
		dm->hit = 1;
		dm->texshift.z = 1;
	}
}

void	part_dda_zp(t_doom *dm, double plane)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5)
			/ dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5)
			/ dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5)
			/ dm->rayd.z;
	if (dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z <= (1 - plane))
		dm->hit = 1;
	part_dda_zp_more(dm, plane);
}
