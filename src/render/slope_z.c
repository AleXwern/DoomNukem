/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_z.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:54:12 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/30 12:45:03 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

t_vector	xz_vect_intersect(t_vector v, t_vector u, t_doom *dm)
{
	t_vector	ret;

	ret = (t_vector){.z = v.z - u.z, .y = v.y - u.y, .x = v.x - u.x};
	ret.y /= ret.z;
	ret.z *= v.y;
	if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
		printf("V XZN %f %f\n", ret.z, ret.y);
	return (ret);
}

void		slope_dda_xzn(t_doom* dm)
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
		if (dm->rmap2.z >= dm->rmap2.y || dm->rmap2.z < LIMN || dm->rmap2.y > LIM)
			return;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("Suitable point XZN\n");
		dm->sided.z += dm->deltad.z;
		dm->map.z += dm->stepz * fabs((dm->rmap1.y - (int)dm->rmap1.y + dm->rmap2.y) / 2);
		dm->side = 2;
		dm->hit = 3;
		dm->hithalf++;
	}
}

void		slope_dda_xzp(t_doom* dm)
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
		dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->tmap.x;
		xz_vect_intersect(dm->rayd, (t_vector){.z = -0.5, .y = -1, .x = 0}, dm);
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("RMAP %.16f < %.16f\n", dm->rmap2.z, dm->rmap2.y);
		if (dm->rmap2.z > dm->rmap2.y || dm->rmap2.z <= LIMN || dm->rmap2.y >= LIM)
		{
			if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
				printf("Suitable point XZP %d\n", dm->side);
			dm->sided.z += dm->deltad.z;
			dm->map.z += dm->stepz * (dm->rmap2.z * (1 - dm->rayd.z));
			dm->side = 2;
			dm->hit = 1;
			dm->hithalf++;
		}
	}
}
