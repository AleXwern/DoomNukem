/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_z.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:54:12 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/09 15:01:19 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	slope_dda_xzn(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y >= (dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z))
		dm->hit = 1;
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("RMAP %f >= %f\n", dm->rmap2.z, dm->rmap2.y);
		if (dm->rmap2.z >= dm->rmap2.y || dm->rmap2.z < LIMN || dm->rmap2.y > LIM)// || dm->rmap2.z > 0)
			return;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("Suitable point\n");
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz * dm->rmap2.y;
		dm->side = 2;
		dm->hit = 3;
		dm->hithalf++;
	}
}

void	slope_dda_xzp(t_doom* dm)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y <= (dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z))
		dm->hit = 1;
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("RMAP %f < %f\n", dm->rmap2.z, dm->rmap2.y);
		if (dm->rmap2.z < dm->rmap2.y)
			return;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("Suitable point XZP\n");
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz * dm->rmap2.y;
		dm->side = 2;
		dm->hit = 1;
		dm->hithalf++;
	}
}
