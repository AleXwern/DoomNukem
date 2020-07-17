/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:48:35 by tbergkul          #+#    #+#             */
/*   Updated: 2020/07/17 13:00:45 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	load_gun4(t_doom *wlf)
{
	wlf->gunRect[5][0].x = 0;
	wlf->gunRect[5][0].y = 640;
	wlf->gunRect[5][0].w = 128;
	wlf->gunRect[5][0].h = 128;
	wlf->gunRect[5][1].x = 128;
	wlf->gunRect[5][1].y = 640;
	wlf->gunRect[5][1].w = 128;
	wlf->gunRect[5][1].h = 128;
	wlf->gunRect[5][2].x = 256;
	wlf->gunRect[5][2].y = 640;
	wlf->gunRect[5][2].w = 128;
	wlf->gunRect[5][2].h = 128;
	wlf->CHSurface = IMG_Load("./gfx/SpriteSheets/crosshair.png");
	wlf->CHTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->CHSurface);
	SDL_FreeSurface(wlf->CHSurface);
	wlf->CHRect.x = 0;
	wlf->CHRect.y = 0;
	wlf->CHRect.w = 340;
	wlf->CHRect.h = 330;
	wlf->screenCHRect.x = (WINX / 2) - 25;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenCHRect.y = (WINY / 2) - 25 ;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenCHRect.w = 50;//width of the final sprite on screen
	wlf->screenCHRect.h = 50;
}

void	load_gun3(t_doom *wlf)
{
	wlf->gunRect[3][0].x = 0;
	wlf->gunRect[3][0].y = 384;
	wlf->gunRect[3][0].w = 128;
	wlf->gunRect[3][0].h = 128;
	wlf->gunRect[3][1].x = 128;
	wlf->gunRect[3][1].y = 384;
	wlf->gunRect[3][1].w = 128;
	wlf->gunRect[3][1].h = 128;
	wlf->gunRect[3][2].x = 256;
	wlf->gunRect[3][2].y = 384;
	wlf->gunRect[3][2].w = 128;
	wlf->gunRect[3][2].h = 128;
	wlf->gunRect[4][0].x = 0;
	wlf->gunRect[4][0].y = 512;
	wlf->gunRect[4][0].w = 128;
	wlf->gunRect[4][0].h = 128;
	wlf->gunRect[4][1].x = 128;
	wlf->gunRect[4][1].y = 512;
	wlf->gunRect[4][1].w = 128;
	wlf->gunRect[4][1].h = 128;
	wlf->gunRect[4][2].x = 256;
	wlf->gunRect[4][2].y = 512;
	wlf->gunRect[4][2].w = 128;
	wlf->gunRect[4][2].h = 128;
	load_gun4(wlf);
}

void	load_gun2(t_doom *wlf)
{
	wlf->gunRect[1][0].x = 0;
	wlf->gunRect[1][0].y = 128;
	wlf->gunRect[1][0].w = 128;
	wlf->gunRect[1][0].h = 128;
	wlf->gunRect[1][1].x = 128;
	wlf->gunRect[1][1].y = 128;
	wlf->gunRect[1][1].w = 128;
	wlf->gunRect[1][1].h = 128;
	wlf->gunRect[1][2].x = 256;
	wlf->gunRect[1][2].y = 128;
	wlf->gunRect[1][2].w = 128;
	wlf->gunRect[1][2].h = 128;
	wlf->gunRect[2][0].x = 0;
	wlf->gunRect[2][0].y = 256;
	wlf->gunRect[2][0].w = 128;
	wlf->gunRect[2][0].h = 128;
	wlf->gunRect[2][1].x = 128;
	wlf->gunRect[2][1].y = 256;
	wlf->gunRect[2][1].w = 128;
	wlf->gunRect[2][1].h = 128;
	wlf->gunRect[2][2].x = 256;
	wlf->gunRect[2][2].y = 256;
	wlf->gunRect[2][2].w = 128;
	wlf->gunRect[2][2].h = 128;
	load_gun3(wlf);
}

/*
**	Gun.png
**	Width: 384
**	Height: 768
**	Each frame is 128x128
*/

void	load_gun(t_doom *wlf)
{
	wlf->gunSurface = IMG_Load("./gfx/SpriteSheets/gun.png");
	wlf->gunTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->gunSurface);
	SDL_FreeSurface(wlf->gunSurface);
	wlf->shooting = 0;
	wlf->reloading = 0;
	wlf->ani = 0;
	wlf->frm = 0;
	wlf->magazine = 10;
	wlf->screenGunRect.x = (wlf->winw / 2) - 16;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenGunRect.y = wlf->winh - 320;//where on screen the upper left corner of the sprite should be drawn
	wlf->screenGunRect.w = 320;//width of the final sprite on screen
	wlf->screenGunRect.h = 320;//height of the final sprite on screen
	wlf->gunRect[0][0].x = 0;//upper left corner x-coordinate
	wlf->gunRect[0][0].y = 0;//upper left corner y-coordinate
	wlf->gunRect[0][0].w = 128;//width of one animation part of the sheet
	wlf->gunRect[0][0].h = 128;//height of one animation part of the sheet
	wlf->gunRect[0][1].x = 128;
	wlf->gunRect[0][1].y = 0;
	wlf->gunRect[0][1].w = 128;
	wlf->gunRect[0][1].h = 128;
	wlf->gunRect[0][2].x = 256;
	wlf->gunRect[0][2].y = 0;
	wlf->gunRect[0][2].w = 128;
	wlf->gunRect[0][2].h = 128;
	load_gun2(wlf);
}

void	draw_gun(t_doom *wlf)
{
	if (!wlf->reloading)
	{
		SDL_RenderCopy(wlf->rend, wlf->gunTexture, &wlf->gunRect[wlf->ani][wlf->frm / 3], &wlf->screenGunRect);
		if (wlf->shooting)
		{
			wlf->frm++;
			if (wlf->ani == 0 && wlf->frm == 1)
				Mix_PlayChannel(-1, wlf->gunshot, 0);
			if ((wlf->frm / 3) > 2)
			{
				if (wlf->ani == 0)
					wlf->ani = 1;
				else
				{
					wlf->ani = 0;
					wlf->shooting = 0;
					wlf->magazine--;
				}
				wlf->frm = 0;
			}
		}
	}
	if (wlf->reloading)
		reloading_gun(wlf);
}
