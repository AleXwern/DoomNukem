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

void	draw_floor(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		wlf->cellx = (int)wlf->floorx;
		wlf->celly = (int)wlf->floory;
		wlf->tx = (int)(128 * (wlf->floorx - wlf->cellx)) & (128 - 1);
		wlf->ty = (int)(128 * (wlf->floory - wlf->celly)) & (128 - 1);
		wlf->img.data[WINX * wlf->y + wlf->x] = color_shift(wlf->gfx[1].data[128 *
			wlf->ty + wlf->tx], wlf->walldist + fabs((double)(wlf->x - WINX / 2) / WINX), wlf);
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
	else
		wlf->img.data[WINX * wlf->y + wlf->x] = 0x0f9926;
}

void	render_floor(t_wolf *wlf)
{
	wlf->raydx0 = wlf->dir.x - wlf->plane.x;
	wlf->raydy0 = wlf->dir.y - wlf->plane.y;
	wlf->raydx1 = wlf->dir.x + wlf->plane.x;
	wlf->raydy1 = wlf->dir.y + wlf->plane.y;
	wlf->rowdist = wlf->walldist;
	wlf->flstepx = wlf->rowdist * (wlf->raydx1 - wlf->raydx0) / WINX;
	wlf->flstepy = wlf->rowdist * (wlf->raydy1 - wlf->raydy0) / WINX;
	wlf->floorx = (wlf->posx + wlf->rowdist * wlf->raydx0) + (wlf->flstepx * wlf->x);
	wlf->floory = (wlf->posy + wlf->rowdist * wlf->raydy0) + (wlf->flstepy * wlf->x);
	draw_floor(wlf);
}
