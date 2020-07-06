/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 01:20:40 by AleXwern          #+#    #+#             */
/*   Updated: 2020/06/30 16:37:45 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

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
	else if (wlf->map[wlf->mapz][wlf->mapy][wlf->mapx] > 2)
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
