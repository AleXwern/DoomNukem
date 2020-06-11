/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 01:20:40 by AleXwern          #+#    #+#             */
/*   Updated: 2020/06/11 13:14:08 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

#include <stdio.h>

void	draw_floor(t_wolf *wlf)
{
	if (wlf->texbool)
	{
		//while (x < wlf->x)
		//{
		wlf->cellx = (int)wlf->floorx;
			wlf->celly = (int)wlf->floory;
			wlf->tx = (int)(128 * (wlf->floorx - wlf->cellx)) & (128 - 1);
			wlf->ty = (int)(128 * (wlf->floory - wlf->celly)) & (128 - 1);
			wlf->floorx += wlf->flstepx;
			wlf->floory += wlf->flstepy;
			wlf->img.data[WINX * wlf->y + wlf->x] = wlf->gfx[1].data[128 *
				wlf->ty + wlf->tx];
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
	//return ;
	//if (wlf->y < WINY / 2)
	//	return ;
	//ft_putendl("thing");
	wlf->raydx0 = wlf->dirx - wlf->planex;
	wlf->raydy0 = wlf->diry - wlf->planey;
	wlf->raydz0 = wlf->dirz - wlf->planez;
	wlf->raydx1 = wlf->dirx + wlf->planex;
	wlf->raydy1 = wlf->diry + wlf->planey;
	wlf->raydz1 = wlf->dirz + wlf->planez;
	//wlf->pos = wlf->y - WINY / 2;
	//wlf->poszz = WINY * 0.5;
	//printf("Cmp: %f %f\n", (double)(wlf->poszz / wlf->pos), wlf->walldist);
	wlf->rowdist = wlf->walldist;
	//if (wlf->poszz / wlf->pos < 0)
	//	wlf->rowdist *= -1;
	//wlf->rowdist = wlf->poszz / wlf->pos;
	wlf->flstepx = wlf->rowdist * (wlf->raydx1 - wlf->raydx0) / WINX;
	wlf->flstepy = wlf->rowdist * (wlf->raydy1 - wlf->raydy0) / WINX;
	wlf->flstepz = wlf->rowdist * (wlf->raydz1 - wlf->raydz0) / WINY;
	wlf->floorx = (wlf->posx + wlf->rowdist * wlf->raydx0) + (wlf->flstepx * wlf->x);
	wlf->floory = (wlf->posy + wlf->rowdist * wlf->raydy0) + (wlf->flstepy * wlf->x);
	wlf->floorz = (wlf->posz + wlf->rowdist * wlf->raydz0) + (wlf->flstepz * wlf->x);
	//ft_putendl("Hello");
	draw_floor(wlf);
}
