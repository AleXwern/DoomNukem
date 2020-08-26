/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadextra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:40:54 by tbergkul          #+#    #+#             */
/*   Updated: 2020/08/26 13:09:37 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/value.h"

void	load_numbers3(t_doom *dm)
{
	dm->screennbrsRect.x = dm->winw - 60;
	dm->screennbrsRect.y = dm->winh - 60;
	dm->screennbrsRect.w = 40;
	dm->screennbrsRect.h = 40;
	dm->screennbrsTenRect.x = dm->winw - 80;
	dm->screennbrsTenRect.y = dm->winh - 60;
	dm->screennbrsTenRect.w = 40;
	dm->screennbrsTenRect.h = 40;
}

void	load_numbers2(t_doom *dm)
{
	dm->nbrsRect[4].x = 200;
	dm->nbrsRect[4].y = 0;
	dm->nbrsRect[4].w = 50;
	dm->nbrsRect[4].h = 50;
	dm->nbrsRect[5].x = 250;
	dm->nbrsRect[5].y = 0;
	dm->nbrsRect[5].w = 50;
	dm->nbrsRect[5].h = 50;
	dm->nbrsRect[6].x = 300;
	dm->nbrsRect[6].y = 0;
	dm->nbrsRect[6].w = 50;
	dm->nbrsRect[6].h = 50;
	dm->nbrsRect[7].x = 350;
	dm->nbrsRect[7].y = 0;
	dm->nbrsRect[7].w = 50;
	dm->nbrsRect[7].h = 50;
	dm->nbrsRect[8].x = 400;
	dm->nbrsRect[8].y = 0;
	dm->nbrsRect[8].w = 50;
	dm->nbrsRect[8].h = 50;
	dm->nbrsRect[9].x = 450;
	dm->nbrsRect[9].y = 0;
	dm->nbrsRect[9].w = 50;
	dm->nbrsRect[9].h = 50;
	load_numbers3(dm);
}

/*
**	numbers.png
**	Width: 500
**	Height: 50
**	Each frame is 50x50
*/

void	load_numbers(t_doom *dm)
{
	dm->nbrsSurface = IMG_Load("./gfx/SpriteSheets/numbers.bmp");
	dm->nbrsTexture = SDL_CreateTextureFromSurface(dm->rend, dm->nbrsSurface);
	SDL_FreeSurface(dm->nbrsSurface);
	dm->nbrsRect[0].x = 0;
	dm->nbrsRect[0].y = 0;
	dm->nbrsRect[0].w = 50;
	dm->nbrsRect[0].h = 50;
	dm->nbrsRect[1].x = 50;
	dm->nbrsRect[1].y = 0;
	dm->nbrsRect[1].w = 50;
	dm->nbrsRect[1].h = 50;
	dm->nbrsRect[2].x = 100;
	dm->nbrsRect[2].y = 0;
	dm->nbrsRect[2].w = 50;
	dm->nbrsRect[2].h = 50;
	dm->nbrsRect[3].x = 150;
	dm->nbrsRect[3].y = 0;
	dm->nbrsRect[3].w = 50;
	dm->nbrsRect[3].h = 50;
	load_numbers2(dm);
}

/*
**	keycard.png
**	Width: 200
**	Height: 140
*/

void	load_keycard(t_doom *dm)
{
	char *test;
	dm->keycardSurface = IMG_Load("./gfx/SpriteSheets/keycard.bmp");
	dm->keycardTexture = SDL_CreateTextureFromSurface(dm->rend, dm->keycardSurface);
	SDL_FreeSurface(dm->keycardSurface);
	dm->keycardRect.x = 0;
	dm->keycardRect.y = 0;
	dm->keycardRect.w = 200;
	dm->keycardRect.h = 140;
	dm->screenkeycardRect.x = 15;
	dm->screenkeycardRect.y = dm->winh - 78;
	dm->screenkeycardRect.w = 70;
	dm->screenkeycardRect.h = 55;
	dm->keycard = 0;
}

void	draw_keycard(t_doom *dm)
{
	SDL_RenderCopy(dm->rend, dm->keycardTexture, &dm->keycardRect, &dm->screenkeycardRect);
}
