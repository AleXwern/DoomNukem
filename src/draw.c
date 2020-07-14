/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/10 14:36:18 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_sky(t_doom *wlf, int scany, int scanx)
{
	if (scanx >= wlf->winw)
		scanx -= wlf->winw;
	scany = abs(wlf->y + 360 * wlf->dir.z) % 360;
	if (wlf->texbool)
		wlf->img.data[wlf->winw * wlf->y + wlf->x] = wlf->gfx[0].data[wlf->winw * scany + wlf->x + scanx];
}

void	draw_stripe(t_doom *wlf)
{
	double	shift;

	if (wlf->texbool)
	{
		shift = (wlf->posz - floor(wlf->posz));
		shift = ((shift - 0.5) * 128);
		if (shift < 0)
			shift = 128 + shift;
		wlf->texy = (int)((((wlf->y * 256 - wlf->winh * 128 * wlf->camshift - wlf->lineh * 128) * 128) / wlf->lineh) / 256) % 128;
		if (wlf->texy < 0)
			wlf->texy += 128;
		wlf->testcolor = color_shift(wlf->gfx[wlf->texnum].data[((wlf->texy + (int)shift) % 128) * wlf->gfx[wlf->texnum].tex->pitch / 4 + wlf->texx % 128 * wlf->gfx[2].tex->format->BitsPerPixel / 32], wlf->walldist + fabs((double)(wlf->x - wlf->winw / 2) / wlf->winw), wlf, 0);
	}
	if (wlf->side > 2)
		wlf->testcolor = (wlf->testcolor >> 1) & DARKEN;
	wlf->img.data[wlf->winw * wlf->y + wlf->x] = wlf->testcolor;

}

void	wall_stripe(t_doom *wlf)
{
	if (wlf->texbool)
	{
		wlf->texnum = wlf->area[(int)wlf->map.z][(int)wlf->map.y][(int)wlf->map.x];
		if (wlf->texnum > 5)//This is a (temporary) fix for the issue where having a value higher than 5 on the map creating a wal with a weird texture.
			wlf->texnum = 2;
		if (wlf->side % 3 == 0)
			wlf->wallx = (wlf->posy + wlf->walldist * wlf->raydy);
		else
			wlf->wallx = (wlf->posx + wlf->walldist * wlf->raydx);
		wlf->wallx -= floor(wlf->wallx);
		wlf->texx = (int)(wlf->wallx * 128.0);
		if (wlf->side == 0 && wlf->raydx > 0)
			wlf->texx = 128 - wlf->texx - 1;
		if (wlf->side == 1 && wlf->raydy < 0)
			wlf->texx = 128 - wlf->texx - 1;
	}
	else if (wlf->area[(int)wlf->map.z][(int)wlf->map.y][(int)wlf->map.x] != 2)
		wlf->testcolor = 0xff22a800;
	draw_stripe(wlf);
}

void	draw_floor(t_doom *wlf)
{
	if (wlf->texbool)
	{
		wlf->cellx = (int)wlf->floorx;
		wlf->celly = (int)wlf->floory;
		wlf->tx = (int)(128 * (wlf->floorx - wlf->cellx)) & (128 - 1);
		wlf->ty = (int)(128 * (wlf->floory - wlf->celly)) & (128 - 1);
		wlf->testcolor = color_shift(wlf->gfx[1].data[128 * wlf->ty + wlf->tx], wlf->walldist + fabs((double)(wlf->x - wlf->winw / 2) / wlf->winw), wlf, 0);
		//wlf->testcolor = wlf->gfx[1].data[128 * wlf->ty + wlf->tx];
	}
	else if (wlf->area[(int)wlf->map.z][(int)wlf->map.y][(int)wlf->map.x] > 2)
		wlf->testcolor = 0xff22a800;
	if (wlf->side > 2)
		wlf->testcolor = (wlf->testcolor >> 1) & DARKEN;
	wlf->img.data[wlf->winw * wlf->y + wlf->x] = wlf->testcolor;
}

void	render_floor(t_doom *wlf)
{
	wlf->raydx0 = wlf->dir.x - wlf->plane.x;
	wlf->raydy0 = wlf->dir.y - wlf->plane.y;
	wlf->raydx1 = wlf->dir.x + wlf->plane.x;
	wlf->raydy1 = wlf->dir.y + wlf->plane.y;
	wlf->rowdist = wlf->walldist;
	wlf->flstepx = wlf->rowdist * (wlf->raydx1 - wlf->raydx0) / wlf->winw;
	wlf->flstepy = wlf->rowdist * (wlf->raydy1 - wlf->raydy0) / wlf->winw;
	wlf->floorx = (wlf->posx + wlf->rowdist * wlf->raydx0) + (wlf->flstepx * wlf->x);
	wlf->floory = (wlf->posy + wlf->rowdist * wlf->raydy0) + (wlf->flstepy * wlf->x);
	draw_floor(wlf);
}
