/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:48:35 by tbergkul          #+#    #+#             */
/*   Updated: 2020/07/22 11:13:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	load_gun4(t_doom *dm)
{
	dm->gunRect[5][0].x = 0;
	dm->gunRect[5][0].y = 640;
	dm->gunRect[5][0].w = 128;
	dm->gunRect[5][0].h = 128;
	dm->gunRect[5][1].x = 128;
	dm->gunRect[5][1].y = 640;
	dm->gunRect[5][1].w = 128;
	dm->gunRect[5][1].h = 128;
	dm->gunRect[5][2].x = 256;
	dm->gunRect[5][2].y = 640;
	dm->gunRect[5][2].w = 128;
	dm->gunRect[5][2].h = 128;
	dm->CHSurface = IMG_Load("/gfx/SpriteSheets/crosshair.xpm");
	dm->CHTexture = SDL_CreateTextureFromSurface(dm->rend, dm->CHSurface);
	SDL_FreeSurface(dm->CHSurface);
	dm->CHRect.x = 0;
	dm->CHRect.y = 0;
	dm->CHRect.w = 340;
	dm->CHRect.h = 330;
	dm->screenCHRect.x = (WINX / 2) - 25;//where on screen the upper left corner of the sprite should be drawn
	dm->screenCHRect.y = (WINY / 2) - 25 ;//where on screen the upper left corner of the sprite should be drawn
	dm->screenCHRect.w = 50;//width of the final sprite on screen
	dm->screenCHRect.h = 50;
}

void	load_gun3(t_doom *dm)
{
	dm->gunRect[3][0].x = 0;
	dm->gunRect[3][0].y = 384;
	dm->gunRect[3][0].w = 128;
	dm->gunRect[3][0].h = 128;
	dm->gunRect[3][1].x = 128;
	dm->gunRect[3][1].y = 384;
	dm->gunRect[3][1].w = 128;
	dm->gunRect[3][1].h = 128;
	dm->gunRect[3][2].x = 256;
	dm->gunRect[3][2].y = 384;
	dm->gunRect[3][2].w = 128;
	dm->gunRect[3][2].h = 128;
	dm->gunRect[4][0].x = 0;
	dm->gunRect[4][0].y = 512;
	dm->gunRect[4][0].w = 128;
	dm->gunRect[4][0].h = 128;
	dm->gunRect[4][1].x = 128;
	dm->gunRect[4][1].y = 512;
	dm->gunRect[4][1].w = 128;
	dm->gunRect[4][1].h = 128;
	dm->gunRect[4][2].x = 256;
	dm->gunRect[4][2].y = 512;
	dm->gunRect[4][2].w = 128;
	dm->gunRect[4][2].h = 128;
	load_gun4(dm);
}

void	load_gun2(t_doom *dm)
{
	dm->gunRect[1][0].x = 0;
	dm->gunRect[1][0].y = 128;
	dm->gunRect[1][0].w = 128;
	dm->gunRect[1][0].h = 128;
	dm->gunRect[1][1].x = 128;
	dm->gunRect[1][1].y = 128;
	dm->gunRect[1][1].w = 128;
	dm->gunRect[1][1].h = 128;
	dm->gunRect[1][2].x = 256;
	dm->gunRect[1][2].y = 128;
	dm->gunRect[1][2].w = 128;
	dm->gunRect[1][2].h = 128;
	dm->gunRect[2][0].x = 0;
	dm->gunRect[2][0].y = 256;
	dm->gunRect[2][0].w = 128;
	dm->gunRect[2][0].h = 128;
	dm->gunRect[2][1].x = 128;
	dm->gunRect[2][1].y = 256;
	dm->gunRect[2][1].w = 128;
	dm->gunRect[2][1].h = 128;
	dm->gunRect[2][2].x = 256;
	dm->gunRect[2][2].y = 256;
	dm->gunRect[2][2].w = 128;
	dm->gunRect[2][2].h = 128;
	load_gun3(dm);
}

/*
**	Gun.png
**	Width: 384
**	Height: 768
**	Each frame is 128x128
*/

void	load_gun(t_doom *dm)
{
	dm->gunSurface = IMG_Load("/gfx/SpriteSheets/gun.xpm");
	dm->gunTexture = SDL_CreateTextureFromSurface(dm->rend, dm->gunSurface);
	SDL_FreeSurface(dm->gunSurface);
	dm->shooting = 0;
	dm->reloading = 0;
	dm->ani = 0;
	dm->frm = 0;
	dm->magazine = 10;
	dm->screenGunRect.x = (dm->winw / 2) - 16;//where on screen the upper left corner of the sprite should be drawn
	dm->screenGunRect.y = dm->winh - 320;//where on screen the upper left corner of the sprite should be drawn
	dm->screenGunRect.w = 320;//width of the final sprite on screen
	dm->screenGunRect.h = 320;//height of the final sprite on screen
	dm->gunRect[0][0].x = 0;//upper left corner x-coordinate
	dm->gunRect[0][0].y = 0;//upper left corner y-coordinate
	dm->gunRect[0][0].w = 128;//width of one animation part of the sheet
	dm->gunRect[0][0].h = 128;//height of one animation part of the sheet
	dm->gunRect[0][1].x = 128;
	dm->gunRect[0][1].y = 0;
	dm->gunRect[0][1].w = 128;
	dm->gunRect[0][1].h = 128;
	dm->gunRect[0][2].x = 256;
	dm->gunRect[0][2].y = 0;
	dm->gunRect[0][2].w = 128;
	dm->gunRect[0][2].h = 128;
	load_gun2(dm);
}

void	draw_gun(t_doom *dm)
{
	if (!dm->reloading)
	{
		SDL_RenderCopy(dm->rend, dm->gunTexture, &dm->gunRect[dm->ani][dm->frm / 3], &dm->screenGunRect);
		if (dm->shooting)
		{
			dm->frm++;
			if (dm->ani == 0 && dm->frm == 1)
				Mix_PlayChannel(-1, dm->gunshot, 0);
			if ((dm->frm / 3) > 2)
			{
				if (dm->ani == 0)
					dm->ani = 1;
				else
				{
					dm->ani = 0;
					dm->shooting = 0;
					dm->magazine--;
				}
				dm->frm = 0;
			}
		}
	}
	if (dm->reloading)
		reloading_gun(dm);
}
