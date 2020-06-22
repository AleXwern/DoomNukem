/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/22 14:41:04 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

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
		//wlf->texy = (int)((((wlf->y * 256 - WINY * 128 - wlf->lineh * 128) * 128) / wlf->lineh) / 256) % 128;
		//wlf->texy = (int)(wlf->texy + (128 * (wlf->walldist - ceil(wlf->walldist)))) % 128;
		if (wlf->texy < 0)
			wlf->texy += 128;
		wlf->testcolor = (Uint32)color_shift(wlf->gfx[wlf->texnum].data[((wlf->texy + (int)shift) % 128) * wlf->gfx[wlf->texnum].tex->pitch / 4 + wlf->texx % 128 * wlf->gfx[2].tex->format->BitsPerPixel / 32], wlf->walldist + fabs((double)(wlf->x - wlf->winw / 2) / wlf->winw), wlf, 0);
	}
	//tar = (Uint32*)wlf->surf->pixels + wlf->y * wlf->surf->pitch + wlf->x * sizeof(*tar);
	//*tar = wlf->testcolor;
	wlf->img.data[wlf->winw * wlf->y + wlf->x] = wlf->testcolor;

}

void	wall_stripe(t_doom *wlf)
{
	if (wlf->texbool)
	{
		wlf->raydy0 = wlf->dir.y - wlf->plane.y;
		wlf->raydy1 = wlf->dir.y + wlf->plane.y;
		wlf->texnum = wlf->map[wlf->mapz][wlf->mapy][wlf->mapx];
		wlf->flstepy = wlf->walldist * (wlf->raydy1 - wlf->raydy0) / wlf->winw;
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
