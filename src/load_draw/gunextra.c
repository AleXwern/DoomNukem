/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gunextra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:34:23 by tbergkul          #+#    #+#             */
/*   Updated: 2020/08/27 14:45:10 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	draw_ammo(t_doom *dm)
{
	if (dm->magazine == 10)
	{
		SDL_RenderCopy(dm->rend, dm->nbrsTexture, &dm->nbrsRect[1], &dm->screennbrsTenRect);
		SDL_RenderCopy(dm->rend, dm->nbrsTexture, &dm->nbrsRect[0], &dm->screennbrsRect);
	}
	else
		SDL_RenderCopy(dm->rend, dm->nbrsTexture, &dm->nbrsRect[dm->magazine], &dm->screennbrsRect);
}

void	draw_crosshair(t_doom *dm)
{
	SDL_RenderCopy(dm->rend, dm->CHTexture, &dm->CHRect, &dm->screenCHRect);
}

void	reloading_gun(t_doom *dm)
{
	//SDL_RenderCopy(dm->rend, dm->gunTexture, &dm->gunRect[dm->ani][dm->frm / 4], &dm->screenGunRect);

	//draw_pgfx_sc(dm, dm->gfx[27], (int[6]){(dm->winh - 320), ((dm->winw / 2) - 16), 160, 160, 0, 0}, 2);
	dm->frm++;
	if (dm->ani == 2 && dm->frm == 1)
		Mix_PlayChannel(-1, dm->reload, 0);
	if ((dm->frm / 4) > 2)
	{
		if (dm->ani < 5)
			dm->ani++;
		else
		{
			dm->ani = 0;
			dm->reloading = 0;
			dm->magazine = 10;
		}
		dm->frm = 0;
	}
}

/*
**	inventory.png
**	Width: 410
**	Height: 120
*/

void	load_inventory(t_doom *dm)
{
	dm->invSurface = IMG_Load("./gfx/SpriteSheets/inventory.bmp");
	dm->invTexture = SDL_CreateTextureFromSurface(dm->rend, dm->invSurface);
	SDL_FreeSurface(dm->invSurface);
	dm->invRect.x = 0;
	dm->invRect.y = 0;
	dm->invRect.w = 410;
	dm->invRect.h = 120;
	dm->screeninvRect.x = -10;
	dm->screeninvRect.y = dm->winh - 110;
	dm->screeninvRect.w = 410;
	dm->screeninvRect.h = 120;
}

void	draw_inventory(t_doom *dm)
{
	SDL_RenderCopy(dm->rend, dm->invTexture, &dm->invRect, &dm->screeninvRect);
}
