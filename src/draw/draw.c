/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/29 10:50:41 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_sky(t_doom *dm)
{
	dm->sbox = 1080 * (1 - atan2(dm->dir.x, dm->dir.y) / M_PI);
	dm->sboy = 360 * (dm->dir.z + 0.9);
	if (dm->texbool)
		dm->col = color_shift(dm->gfx[23].data[1080 * ((dm->y + dm->sboy) % 360)
			+ (dm->x + dm->sbox) % 1080], 6, dm, 0);
	else
		dm->col = 0xff000000;
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
	dm->maparr[dm->winw * dm->y + dm->x] = -1;
}

void	draw_floor(t_doom *dm)
{
	if (dm->texbool)
	{
		dm->cellx = (int)dm->floor.x;
		dm->celly = (int)dm->floor.y;
		dm->tx = (int)(128 * (dm->floor.x - dm->cellx)) & (128 - 1);
		dm->ty = (int)(128 * (dm->floor.y - dm->celly)) & (128 - 1);
		dm->col = color_shift(dm->gfx[dm->texnum].data[128 * dm->ty +
			dm->tx], dm->walldist + fabs((double)(dm->x - dm->winw / 2) /
			dm->winw), dm, 0);
		dm->lgt = light_map(dm->map, dm->side, dm->area);
		dm->col = rl_color(dm->lgt, dm->col);
	}
	else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b > 2)
		dm->col = 0xff22a800;
	if (dm->side > 2)
		dm->col = (dm->col >> 1) & DARKEN;
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
}

void	render_floor(t_doom *dm)
{
	dm->texnum = 1;
	if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b == 6)
		dm->texnum = 6;
	dm->rayd0.x = dm->dir.x - dm->plane.x;
	dm->rayd0.y = dm->dir.y - dm->plane.y;
	dm->rayd1.x = dm->dir.x + dm->plane.x;
	dm->rayd1.y = dm->dir.y + dm->plane.y;
	dm->flstep.x = dm->walldist * (dm->rayd1.x - dm->rayd0.x) / dm->winw;
	dm->flstep.y = dm->walldist * (dm->rayd1.y - dm->rayd0.y) / dm->winw;
	dm->floor.x = (dm->pos.x + dm->walldist * dm->rayd0.x)
		+ (dm->flstep.x * dm->x);
	dm->floor.y = (dm->pos.y + dm->walldist * dm->rayd0.y)
		+ (dm->flstep.y * dm->x);
	draw_floor(dm);
	if (dm->wincol)
		ext_ray(dm);
}
