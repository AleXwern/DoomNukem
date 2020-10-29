/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope_xyt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:57:39 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/16 15:42:17 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

static double	create_plane_xyt(t_vector rayd, t_vector rmap, t_doom *dm, int side)
{
	t_vector	plane[2];
	t_vector	point;
	t_vector	ray[2];

	plane[0] = (t_vector){
		.z = 0, .y = 0, .x = 0
	};
	plane[1] = (t_vector){
		.z = 0, .y = 1, .x = 1
	};
	ray[0] = (t_vector){.z = rmap.z - (int)rmap.z, .y = rmap.y - (int)rmap.y, .x = rmap.x - (int)rmap.x};
	ray[1] = rayd;
	intersect(plane, ray, &point);
	if (dm->x == 500 && dm->y == 360)
		printf("Cross point %f %f %f at %d\nRMAP %f %f %f and %f\n", point.z, point.y, point.x, side, ray[0].z, ray[0].y, ray[0].x, dm->rayd.x);
	if (point.y >= 0 && point.y <= 1)
		return (point.y);
	return (1);
}

void	slope_dda_xyt(t_doom* dm, int side)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x <= 1 - (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y))
		dm->hit = 1;
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->tmap.x;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("XZTN %.16f < %.16f\n", dm->rmap2.x, dm->rmap2.y);
		if ((dm->rmap2.y < 1 - dm->rmap2.x || dm->rmap2.y > LIM || dm->rmap2.x >= LIM)
			&& dm->rmap2.y > LIMN && dm->rmap2.x > LIMN)
		{
			dm->stepy = 1;
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy * create_plane_xyt(dm->rayd, dm->rmap1, dm, side);
			dm->side = 1;
			dm->hit = 1;
			dm->hithalf++;
		}
	}
}

void	slope_dda_xytr(t_doom* dm, int side)
{
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->map.x >= 1 - (dm->pos.y + (dm->rayd.y * dm->walldist) - (int)dm->map.y))
		dm->hit = 1;
	if (dm->hit != 1)
	{
		dm->rmap1.z = dm->pos.z + (dm->rayd.z * dm->walldist);
		dm->rmap1.y = dm->pos.y + (dm->rayd.y * dm->walldist);
		dm->rmap1.x = dm->pos.x + (dm->rayd.x * dm->walldist);
		single_loop_y(dm);
		dm->rmap2.x = dm->pos.x + (dm->rayd.x * dm->walldist) - (int)dm->tmap.x;
		if (dm->x == dm->winw / 2 && dm->y == dm->winh / 2)
			printf("XZTR %.16f < %.16f\n", dm->rmap2.x, dm->rmap2.y);
		if ((dm->rmap2.y > 1 - dm->rmap2.x || dm->rmap2.y < LIMN || dm->rmap2.x <= LIMN)
			&& dm->rmap2.y < LIM && dm->rmap2.x < LIM)
		{
			dm->stepy = 1;
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy * create_plane_xyt(dm->rayd, dm->rmap1, dm, side);
			dm->side = 1;
			dm->hit = 1;
			dm->hithalf++;
		}
	}
}