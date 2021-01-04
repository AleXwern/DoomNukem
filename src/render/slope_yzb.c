/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_yzb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:54:12 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 14:36:19 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

static double	create_plane_yzb(t_vector rayd, t_vector rmap,
	t_doom *dm, int side)
{
	t_vector	plane[2];
	t_vector	point;
	t_vector	ray[2];

	plane[0] = (t_vector){
		.z = 0, .y = 0, .x = 0
	};
	plane[1] = (t_vector){
		.z = 1, .y = -1, .x = 0
	};
	ray[0] = (t_vector){.z = rmap.z - (int)rmap.z, .y = rmap.y - (int)rmap.y,
		.x = rmap.x - (int)rmap.x};
	ray[1] = rayd;
	if (side == 1 && dm->rayd.y < 0)
		ray[0].y = 1;
	else if (side == 2 && dm->rayd.z < 0)
		ray[0].z = 1;
	intersect(plane, ray, &point);
	if (point.z >= 0 && point.z <= 1)
		return (point.z);
	return (1);
}

void			slope_dda_yzb_more(t_doom *dm, int side)
{
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
		if ((dm->rmap2.z > dm->rmap2.y || dm->rmap2.z <= LIMN ||
			dm->rmap2.y >= LIM) && dm->rmap2.z < LIM && dm->rmap2.y > LIMN)
		{
			dm->stepz = 1;
			dm->sided.z += dm->deltad.z;
			dm->map.z += dm->stepz *
				create_plane_yzb(dm->rayd, dm->rmap1, dm, side);
			dm->side = 2;
			dm->hit = 1;
			dm->flag = 2;
		}
	}
}

void			slope_dda_yzb(t_doom *dm, int side)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y <=
		(dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z))
		dm->hit = 1;
	slope_dda_yzb_more(dm, side);
}

void			slope_dda_yzbr_more(t_doom *dm, int side)
{
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_z(dm);
		dm->rmap2.y = dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->tmap.y;
		if ((dm->rmap2.z < dm->rmap2.y || dm->rmap2.z >= LIM ||
			dm->rmap2.y <= LIMN) && dm->rmap2.z > LIMN && dm->rmap2.y < LIM)
		{
			dm->stepz = 1;
			dm->sided.z += dm->deltad.z;
			dm->map.z += dm->stepz *
				create_plane_yzb(dm->rayd, dm->rmap1, dm, side);
			dm->side = 2;
			dm->hit = 1;
			dm->flag = 1;
		}
	}
}

void			slope_dda_yzbr(t_doom *dm, int side)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x +
			(1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y +
			(1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z +
			(1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y >=
		(dm->pos.z + (dm->rayd.z * dm->walldist) - (int)dm->map.z))
		dm->hit = 1;
	slope_dda_yzbr_more(dm, side);
}
