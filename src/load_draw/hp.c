/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:40:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/08/26 14:31:28 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

/*void	load_hp3(t_doom *dm)
{
	dm->screenhpRect.x = dm->winw - 60;
	dm->screenhpRect.y = dm->winh - 60;
	dm->screenhpRect.w = 40;
	dm->screenhpRect.h = 40;
	dm->screenhpTenRect.x = dm->winw - 80;
	dm->screenhpTenRect.y = dm->winh - 60;
	dm->screenhpTenRect.w = 40;
	dm->screenhpTenRect.h = 40;
}*/

void	load_hp2(t_doom *dm)
{
	dm->hpRect[4].x = 0;
	dm->hpRect[4].y = 349;
	dm->hpRect[4].w = 367;
	dm->hpRect[4].h = 90;
	dm->hpRect[5].x = 0;
	dm->hpRect[5].y = 441;
	dm->hpRect[5].w = 367;
	dm->hpRect[5].h = 90;
	dm->screenhpRect.x = 20;
	dm->screenhpRect.y = 10;
	dm->screenhpRect.w = 367;
	dm->screenhpRect.h = 90;
	dm->hp = 100;
	dm->alive = 1;
	dm->healthBar[0] = 5;
	dm->healthBar[1] = 4;
	dm->healthBar[2] = 3;
	dm->healthBar[3] = 2;
	dm->healthBar[4] = 1;
	dm->healthBar[5] = 0;
}

/*
**	healthBar.png
**	Width: 458		367
**	Height: 544		539
**	Each frame is 367x89.83
*/

void	load_hp(t_doom *dm)
{
	dm->hpSurface = IMG_Load("./gfx/SpriteSheets/healthBar.bmp");
	dm->hpTexture = SDL_CreateTextureFromSurface(dm->rend, dm->hpSurface);
	SDL_FreeSurface(dm->hpSurface);
	dm->hpRect[0].x = 0;
	dm->hpRect[0].y = 0;
	dm->hpRect[0].w = 367;
	dm->hpRect[0].h = 90;
	dm->hpRect[1].x = 0;
	dm->hpRect[1].y = 86;
	dm->hpRect[1].w = 367;
	dm->hpRect[1].h = 90;
	dm->hpRect[2].x = 0;
	dm->hpRect[2].y = 171;
	dm->hpRect[2].w = 367;
	dm->hpRect[2].h = 90;
	dm->hpRect[3].x = 0;
	dm->hpRect[3].y = 261;
	dm->hpRect[3].w = 367;
	dm->hpRect[3].h = 90;
	load_hp2(dm);
}

/*void	draw_hp(t_doom *dm)
{
	int	healthBar;

	if (dm->hp > 0)
		healthBar = dm->healthBar[(dm->hp / 20)];
	else
		healthBar = 5;
	SDL_RenderCopy(dm->rend, dm->hpTexture, &dm->hpRect[healthBar], &dm->screenhpRect);
}*/

void	draw_hp(t_doom *dm, t_gfx gfx, int x, int y)
{
	int	gx;
	int	gy;
	int	healthBar;

	if (dm->hp > 0)
		healthBar = dm->healthBar[(dm->hp / 20)];
	else
		healthBar = 5;
	gy = 0;
	while (gy < gfx.hgt && (y + gy) < dm->winh)
	{
		gx = 0;
		while (gx < gfx.wid && (x + gx) < dm->winw)
		{
			if (gfx.data[gfx.wid * gy + gx] != 0xffff00ff)
				dm->img.data[dm->winw * (y + gy) + (x + gx)] = gfx.data[gfx.wid *
					gy + gx];
			gx++;
		}
		gy++;
	}
}
