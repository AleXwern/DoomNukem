/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_dda_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:33:20 by tbergkul          #+#    #+#             */
/*   Updated: 2020/10/30 14:38:21 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	single_loop_z_more(t_doom *dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.z = dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->tmap.z;
}

void	single_loop_y_more(t_doom *dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
}

void	single_loop_x_more(t_doom *dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->tmap.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->tmap.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->tmap.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->tmap.x;
}
