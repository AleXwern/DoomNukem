/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/11 16:48:47 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	draw_stripe(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		double	shift = (wlf->posz - floor(wlf->posz));
		shift = (((shift) - 0.5) * 128);
		if (shift < 0)
			shift = 128 + shift;
		wlf->texy = ((int)(((wlf->y * 256 - WINY * 128 - wlf->lineh
				* 128) * 128)
					/ wlf->lineh) / 256);
		if (wlf->texy < 0)
			wlf->texy += 128 * ceil(fabs((double)wlf->texy / 128));
		wlf->testcolor = wlf->gfx[wlf->texnum].data[((wlf->texy + (int)shift) % 128) *
				wlf->gfx[wlf->texnum].sizel / 4 + wlf->texx %
				128 * wlf->gfx[2].bpp / 32];
	}
	wlf->img.data[WINX * wlf->y + wlf->x] = wlf->testcolor;
}

void	wall_stripe(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		wlf->texnum = wlf->map[wlf->mapz][wlf->mapy][wlf->mapx];
		if (wlf->side == 0)
			wlf->wallx = wlf->posy + wlf->walldist * wlf->raydy;
		else
			wlf->wallx = wlf->posx + wlf->walldist * wlf->raydx;
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
