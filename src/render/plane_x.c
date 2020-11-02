/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:24:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/30 14:40:19 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	part_dda_xn(t_doom *dm, double plane)
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
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x >= plane)
		dm->hit = 1;
	if (dm->rayd.x > 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_x(dm);
		if (dm->rmap2.x < plane && dm->rmap2.x > 0)
			return ;
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx * plane;
		dm->side = 0;
		dm->hit = 1;
	}
}

void	part_dda_xp_more(t_doom *dm, double plane)
{
	if (dm->rayd.x < 0 && dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_x(dm);
		if (dm->rmap2.x > (1 - plane) && dm->rmap2.x < LIM)
			return ;
		dm->sided.x += dm->deltad.x;
		dm->map.x += dm->stepx * plane;
		dm->side = 0;
		dm->hit = 1;
		dm->texshift.x = 1;
	}
}

void	part_dda_xp(t_doom *dm, double plane)
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
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x <= (1 - plane))
		dm->hit = 1;
	part_dda_xp_more(dm, plane);
}
