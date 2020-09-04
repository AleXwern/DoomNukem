/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:21:56 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/04 15:24:13 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	ext_dda(t_doom *dm)
{
	dm->hit = 0;
	while (dm->hit == 0)
	{
		if (dm->sided.x < dm->sided.y && dm->sided.x < dm->sided.z)
		{
			dm->sided.x += dm->deltad.x;
			dm->map.x += dm->stepx;
			dm->side = 0;
		}
		else if (dm->sided.y < dm->sided.x && dm->sided.y < dm->sided.z)
		{
			dm->sided.y += dm->deltad.y;
			dm->map.y += dm->stepy;
			dm->side = 1;
		}
		else
		{
			dm->sided.z += dm->deltad.z;
			dm->map.z += dm->stepz;
			dm->side = 2;
		}
		if (dm->map.z < 0 || dm->map.y < 0 || dm->map.x < 0 || dm->map.z >= 9 || dm->map.y >= 25 || dm->map.x >= 25)
		{
			dm->hit = 2;
			return;
		}
		if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 6)
			dm->hit = 0;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].pt
				&& dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 1)
			part_check(dm);
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 6)
			dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b = 1;
		else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 1)
			dm->hit = 1;
	}
}

void	ext_raytwo(t_doom *dm)
{
	if (dm->side % 3 == 1)
		dm->col = 0xff3679ff;
	else if (dm->side % 3 == 2)
		dm->col = 0xffb01cff;
	else
		dm->col = 0xffF0330A;
	dm->wallarr[dm->winw * dm->y + dm->x] = dm->walldist;
	dm->maparr[dm->winw * dm->y + dm->x] = dm->side + 1 + dm->map.z + dm->map.y + dm->map.x;
	dm->wincol = 0;
	if (dm->hit == 2)
		draw_sky(dm);
	else if (dm->hit == 3)
		dm->img.data[dm->winw * dm->y + dm->x] = 0xff000000;
	else if (dm->side == 2 || dm->side == 5)
		render_floor(dm);
	else
		wall_stripe(dm);
	dm->col = avg_color(dm->rcol, dm->col);
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
}

void	ext_ray(t_doom *dm)
{
	ext_dda(dm);
	if (dm->side == 0)
		dm->walldist = (dm->map.x - dm->pos.x + (1 - dm->stepx) * 0.5) / dm->rayd.x;
	else if (dm->side == 1)
		dm->walldist = (dm->map.y - dm->pos.y + (1 - dm->stepy) * 0.5) / dm->rayd.y;
	else
		dm->walldist = (dm->map.z - dm->pos.z + (1 - dm->stepz) * 0.5) / dm->rayd.z;
	if (dm->walldist < 0.0001)
		dm->walldist += 0.01;
	dm->lineh = (dm->winh / dm->walldist);
	side_check(dm);
	dm->rcol = dm->col;
	ext_raytwo(dm);
}