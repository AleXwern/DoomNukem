/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_xyt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:57:39 by anystrom          #+#    #+#             */
/*   Updated: 2021/01/04 14:35:33 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

static double	create_plane_xyt(t_vector rayd, t_vector rmap,
	t_doom *dm, int side)
{
	t_vector	plane[2];
	t_vector	point;
	t_vector	ray[2];

	plane[0] = (t_vector){.z = 0, .y = 0, .x = 0};
	plane[1] = (t_vector){.z = 0, .y = 1, .x = 1};
	ray[0] = (t_vector){.z = rmap.z - (int)rmap.z, .y = rmap.y - (int)rmap.y,
		.x = rmap.x - (int)rmap.x};
	ray[1] = rayd;
	if (dm->rayd.x > 0 && side == 0)
		ray[0].x = -1;
	else if (side)
		ray[0].x -= 1;
	if (side == 1 && dm->rayd.y < 0 && ray[0].y < 0.5)
		ray[0].y += 1;
	intersect(plane, ray, &point);
	if (point.y >= 0 && point.y <= 1)
		return (point.y);
	return (1);
}

void			slope_dda_xyt_more(t_doom *dm, int side)
{
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) -
			(int)dm->tmap.x;
		if ((dm->rmap2.y < 1 - dm->rmap2.x || dm->rmap2.y > LIM ||
			dm->rmap2.x >= LIM) && dm->rmap2.y > LIMN && dm->rmap2.x > LIMN)
		{
			dm->stepy = 1;
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy *
				create_plane_xyt(dm->rayd, dm->rmap1, dm, side);
			dm->side = 1;
			dm->hit = 1;
			dm->flag = 1;
		}
	}
}

void			slope_dda_xyt(t_doom *dm, int side)
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
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x <=
		1 - (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y))
		dm->hit = 1;
	slope_dda_xyt_more(dm, side);
}

void			slope_dda_xytr_more(t_doom *dm, int side)
{
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) -
			(int)dm->tmap.x;
		if ((dm->rmap2.y > 1 - dm->rmap2.x || dm->rmap2.y < LIMN ||
			dm->rmap2.x <= LIMN) && dm->rmap2.y < LIM && dm->rmap2.x < LIM)
		{
			dm->stepy = 1;
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy *
				create_plane_xyt(dm->rayd, dm->rmap1, dm, side);
			dm->side = 1;
			dm->hit = 1;
			dm->flag = 2;
		}
	}
}

void			slope_dda_xytr(t_doom *dm, int side)
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
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x >=
		1 - (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y))
		dm->hit = 1;
	slope_dda_xytr_more(dm, side);
}
