/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gunextra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:34:23 by tbergkul          #+#    #+#             */
/*   Updated: 2020/07/17 14:21:31 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	draw_ammo(t_doom *wlf)
{
	if (wlf->magazine == 10)
	{
		SDL_RenderCopy(wlf->rend, wlf->nbrsTexture, &wlf->nbrsRect[1], &wlf->screennbrsTenRect);
		SDL_RenderCopy(wlf->rend, wlf->nbrsTexture, &wlf->nbrsRect[0], &wlf->screennbrsRect);
	}
	else
		SDL_RenderCopy(wlf->rend, wlf->nbrsTexture, &wlf->nbrsRect[wlf->magazine], &wlf->screennbrsRect);
}

void	draw_crosshair(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->CHTexture, &wlf->CHRect, &wlf->screenCHRect);
}

void	reloading_gun(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->gunTexture, &wlf->gunRect[wlf->ani][wlf->frm / 4], &wlf->screenGunRect);
	wlf->frm++;
	if (wlf->ani == 2 && wlf->frm == 1)
		Mix_PlayChannel(-1, wlf->reload, 0);
	if ((wlf->frm / 4) > 2)
	{
		if (wlf->ani < 5)
			wlf->ani++;
		else
		{
			wlf->ani = 0;
			wlf->reloading = 0;
			wlf->magazine = 10;
		}
		wlf->frm = 0;
	}
}

/*
**	inventory.png
**	Width: 410
**	Height: 120
*/

void	load_inventory(t_doom *wlf)
{
	wlf->invSurface = IMG_Load("./gfx/SpriteSheets/inventory.png");
	wlf->invTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->invSurface);
	SDL_FreeSurface(wlf->invSurface);
	wlf->invRect.x = 0;
	wlf->invRect.y = 0;
	wlf->invRect.w = 410;
	wlf->invRect.h = 120;
	wlf->screeninvRect.x = -10;
	wlf->screeninvRect.y = wlf->winh - 110;
	wlf->screeninvRect.w = 410;
	wlf->screeninvRect.h = 120;
}

void	draw_inventory(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->invTexture, &wlf->invRect, &wlf->screeninvRect);
}
