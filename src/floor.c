/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 01:20:40 by AleXwern          #+#    #+#             */
/*   Updated: 2020/06/17 16:37:20 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	draw_floor(t_doom *wlf)
{
	Uint32* tex;
	Uint32* src;

	if (wlf->texbool)
	{
		tex = (Uint32*)wlf->gfx[1].tex->pixels;
		wlf->cellx = (int)wlf->floorx;
		wlf->celly = (int)wlf->floory;
		wlf->tx = (int)(128 * (wlf->floorx - wlf->cellx)) & (128 - 1);
		wlf->ty = (int)(128 * (wlf->floory - wlf->celly)) & (128 - 1);
		wlf->testcolor = color_shift(tex[128 *
			wlf->ty + wlf->tx], wlf->walldist + fabs((double)(wlf->x - wlf->winw / 2) / wlf->winw), wlf);
		//}
		//printf("Write to %d from %d\n", WINX * wlf->y + wlf->x, 128 * wlf->ty + wlf->tx);
		/*printf("\nEndvalues:\nRay0: %f %f\nRay1: %f %f\nPos: %d %f\nRowD: %f\nFLstep: %f %f\nCell: %d %d\nTX: %d %d\nFloor: %f %f\n\n", 
				wlf->raydx0, 
				wlf->raydy0, 
				wlf->raydx1, 
				wlf->raydy1, 
				wlf->pos, 
				wlf->poszz, 
				wlf->rowdist, 
				wlf->flstepx, 
				wlf->flstepy, 
				wlf->cellx, 
				wlf->celly, 
				wlf->tx, 
				wlf->ty, 
				wlf->floorx, 
				wlf->floory);*/
	}
	src = (Uint32*)wlf->surf->pixels;
	src[wlf->winw * wlf->y + wlf->x] = wlf->testcolor;
	wlf->surf->pixels = src;
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
