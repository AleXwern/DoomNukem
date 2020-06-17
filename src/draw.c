/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/17 16:41:17 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_gfx(t_wolf *wlf, t_gfx gfx, int x, int y)
{
	int		gx;
	int		gy;

	gy = 0;
	while (gy < gfx.hgt)
	{
		gx = 0;
		while (gx < gfx.wid)
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xff00ff)
				wlf->img.data[WINX * (y + gy) + (x + gx)] = gfx.data[gfx.wid *
						gy + gx];
			gx++;
		}
		gy++;
	}
}

void	draw_stripe(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		double	shift = (wlf->posz - floor(wlf->posz));
		shift = ((shift - 0.5) * 128);
		if (shift < 0)
			shift = 128 + shift;
		wlf->texy = (int)((((wlf->y * 256 - WINY * 128 - wlf->lineh
				* 128) * 128)
					/ wlf->lineh) / 256) % 128;
		//wlf->texy = (int)(wlf->texy + (128 * (wlf->walldist - ceil(wlf->walldist)))) % 128;
		if (wlf->texy < 0)
			wlf->texy += 128;
		wlf->testcolor = color_shift(wlf->gfx[wlf->texnum].data[((wlf->texy + (int)shift) % 128) *
				wlf->gfx[wlf->texnum].sizel / 4 + wlf->texx %
				128 * wlf->gfx[2].bpp / 32], wlf->walldist + fabs((double)(wlf->x - WINX / 2) / WINX), wlf);
	}
	wlf->img.data[WINX * wlf->y + wlf->x] = wlf->testcolor;
}

void	wall_stripe(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		wlf->raydy0 = wlf->dir.y - wlf->plane.y;
		wlf->raydy1 = wlf->dir.y + wlf->plane.y;
		wlf->texnum = wlf->map[wlf->mapz][wlf->mapy][wlf->mapx];
		wlf->flstepy = wlf->walldist * (wlf->raydy1 - wlf->raydy0) / WINX;
		if (wlf->side == 0)
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
	else if (wlf->map[wlf->mapz][wlf->mapy][wlf->mapx] != 2)
		wlf->testcolor = 0x22a800;
	draw_stripe(wlf);
}
