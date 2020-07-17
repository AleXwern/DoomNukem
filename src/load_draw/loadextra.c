/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadextra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:40:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/07/17 14:33:43 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	load_numbers3(t_doom *wlf)
{
	wlf->screennbrsRect.x = wlf->winw - 60;
	wlf->screennbrsRect.y = wlf->winh - 60;
	wlf->screennbrsRect.w = 40;
	wlf->screennbrsRect.h = 40;
	wlf->screennbrsTenRect.x = wlf->winw - 80;
	wlf->screennbrsTenRect.y = wlf->winh - 60;
	wlf->screennbrsTenRect.w = 40;
	wlf->screennbrsTenRect.h = 40;
}

void	load_numbers2(t_doom *wlf)
{
	wlf->nbrsRect[4].x = 200;
	wlf->nbrsRect[4].y = 0;
	wlf->nbrsRect[4].w = 50;
	wlf->nbrsRect[4].h = 50;
	wlf->nbrsRect[5].x = 250;
	wlf->nbrsRect[5].y = 0;
	wlf->nbrsRect[5].w = 50;
	wlf->nbrsRect[5].h = 50;
	wlf->nbrsRect[6].x = 300;
	wlf->nbrsRect[6].y = 0;
	wlf->nbrsRect[6].w = 50;
	wlf->nbrsRect[6].h = 50;
	wlf->nbrsRect[7].x = 350;
	wlf->nbrsRect[7].y = 0;
	wlf->nbrsRect[7].w = 50;
	wlf->nbrsRect[7].h = 50;
	wlf->nbrsRect[8].x = 400;
	wlf->nbrsRect[8].y = 0;
	wlf->nbrsRect[8].w = 50;
	wlf->nbrsRect[8].h = 50;
	wlf->nbrsRect[9].x = 450;
	wlf->nbrsRect[9].y = 0;
	wlf->nbrsRect[9].w = 50;
	wlf->nbrsRect[9].h = 50;
	load_numbers3(wlf);
}

/*
**	numbers.png
**	Width: 500
**	Height: 50
**	Each frame is 50x50
*/

void	load_numbers(t_doom *wlf)
{
	wlf->nbrsSurface = IMG_Load("./gfx/SpriteSheets/numbers.png");
	wlf->nbrsTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->nbrsSurface);
	SDL_FreeSurface(wlf->nbrsSurface);
	wlf->nbrsRect[0].x = 0;
	wlf->nbrsRect[0].y = 0;
	wlf->nbrsRect[0].w = 50;
	wlf->nbrsRect[0].h = 50;
	wlf->nbrsRect[1].x = 50;
	wlf->nbrsRect[1].y = 0;
	wlf->nbrsRect[1].w = 50;
	wlf->nbrsRect[1].h = 50;
	wlf->nbrsRect[2].x = 100;
	wlf->nbrsRect[2].y = 0;
	wlf->nbrsRect[2].w = 50;
	wlf->nbrsRect[2].h = 50;
	wlf->nbrsRect[3].x = 150;
	wlf->nbrsRect[3].y = 0;
	wlf->nbrsRect[3].w = 50;
	wlf->nbrsRect[3].h = 50;
	load_numbers2(wlf);
}

/*
**	keycard.png
**	Width: 200
**	Height: 140
*/

void	load_keycard(t_doom *wlf)
{
	wlf->keycardSurface = IMG_Load("./gfx/SpriteSheets/keycard.png");
	wlf->keycardTexture = SDL_CreateTextureFromSurface(wlf->rend, wlf->keycardSurface);
	SDL_FreeSurface(wlf->keycardSurface);
	wlf->keycardRect.x = 0;
	wlf->keycardRect.y = 0;
	wlf->keycardRect.w = 200;
	wlf->keycardRect.h = 140;
	wlf->screenkeycardRect.x = 20;
	wlf->screenkeycardRect.y = wlf->winh - 55;
	wlf->screenkeycardRect.w = 50;
	wlf->screenkeycardRect.h = 50;
}

void	draw_keycard(t_doom *wlf)
{
	SDL_RenderCopy(wlf->rend, wlf->keycardTexture, &wlf->keycardRect, &wlf->screenkeycardRect);
}
