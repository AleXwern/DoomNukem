/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/09 12:48:12 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_sky(t_doom *dm)
{
	while (dm->sbox >= dm->winw)
		dm->sbox -= dm->winw;
	while (dm->sboy >= dm->winh)
		dm->sboy -= dm->winh;
	while (dm->sbox < 0)
		dm->sbox += dm->winw;
	while (dm->sboy < 0)
		dm->sboy += dm->winh;
	if (dm->texbool)
		dm->col = dm->gfx[0].data[dm->winw * ((dm->y + dm->sboy) % 360) + (dm->x + dm->sbox) % 1080];
	else
		dm->col = 0xff000000;
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
}

void	draw_stripe(t_doom *dm)
{
	double	shift;

	if (dm->texbool)
	{
		shift = (dm->pos.z - floor(dm->pos.z));
		shift = ((shift - 0.5) * 128);
		if (shift < 0)
			shift = 128 + shift;
		dm->texy = (int)((((dm->y * 256 - dm->winh * 128 * dm->camshift - dm->lineh * 128) * 128) / dm->lineh) / 256) % 128;
		if (dm->texy < 0)
			dm->texy += 128;
		dm->col = color_shift(dm->gfx[dm->texnum].data[((dm->texy + (int)shift) % 128) * 128 + dm->texx % 128], dm->walldist + fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
		dm->lgt = light_map(dm->map, dm->side, dm->area);
		dm->col = rl_color(dm->lgt, dm->col);
	}
	if (dm->side > 2)
		dm->col = (dm->col >> 1) & DARKEN;
	dm->img.data[dm->winw * dm->y + dm->x] = dm->col;
}

void	wall_stripe(t_doom *dm)
{
	if (dm->texbool)
	{
		dm->texnum = dm->area[(int)ceil(dm->map.z)][(int)ceil(dm->map.y)][(int)ceil(dm->map.x)].b;
		if (dm->texnum > 6)//This is a (temporary) fix for the issue where having a value higher than 5 on the map creating a wal with a weird texture.
			dm->texnum = 2;
		if (dm->side % 3 == 0)
			dm->wallx = (dm->pos.y + dm->walldist * dm->rayd.y);
		else
			dm->wallx = (dm->pos.x + dm->walldist * dm->rayd.x);
		dm->wallx -= floor(dm->wallx);
		dm->texx = (int)(dm->wallx * 128.0);
		if (dm->side == 0 && dm->rayd.x > 0)
			dm->texx = 128 - dm->texx - 1;
		else if (dm->side == 1 && dm->rayd.y < 0)
			dm->texx = 128 - dm->texx - 1;
	}
	else if (dm->area[(int)dm->map.z][(int)dm->map.y][(int)dm->map.x].b != 2)
		dm->col = 0xff22a800;
	draw_stripe(dm);
	if (dm->wincol)
		ext_ray(dm);
}

void	draw_floor(t_doom *dm)
{
	if (dm->texbool)
	{
		dm->cellx = (int)dm->floor.x;
		dm->celly = (int)dm->floor.y;
		dm->tx = (int)(128 * (dm->floor.x - dm->cellx)) & (128 - 1);
		dm->ty = (int)(128 * (dm->floor.y - dm->celly)) & (128 - 1);
		if ((dm->rayd.z < 0 && !dm->area[(int)dm->map.z + 1][(int)dm->map.y][(int)dm->map.x].b) || (dm->rayd.z > 0 && !dm->area[(int)dm->map.z - 1][(int)dm->map.y][(int)dm->map.x].b))
			dm->col = color_shift(dm->gfx[5].data[128 * dm->ty + dm->tx], dm->walldist + fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
		else
			dm->col = color_shift(dm->gfx[dm->texnum].data[128 * dm->ty + dm->tx], dm->walldist + fabs((double)(dm->x - dm->winw / 2) / dm->winw), dm, 0);
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
	dm->rowdist = dm->walldist;
	dm->flstep.x = dm->rowdist * (dm->rayd1.x - dm->rayd0.x) / dm->winw;
	dm->flstep.y = dm->rowdist * (dm->rayd1.y - dm->rayd0.y) / dm->winw;
	dm->floor.x = (dm->pos.x + dm->rowdist * dm->rayd0.x) + (dm->flstep.x * dm->x);
	dm->floor.y = (dm->pos.y + dm->rowdist * dm->rayd0.y) + (dm->flstep.y * dm->x);
	draw_floor(dm);
	if (dm->wincol)
		ext_ray(dm);
}
