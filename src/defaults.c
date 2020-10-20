/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:00:00 by anystrom          #+#    #+#             */
/*   Updated: 2020/10/20 12:40:42 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	wind_default(t_doom *dm)
{
	dm->shift = 15;
	dm->crouching = 0;
	dm->mousemovement = 0;
	dm->fps = 0;
	dm->plane.x = dm->plane.x * ((double)dm->owinh / (double)dm->owinw);
	dm->plane.y = dm->plane.y * ((double)dm->owinh / (double)dm->owinw);
	dm->plane.x = dm->plane.x / ((double)dm->winh / (double)dm->winw);
	dm->plane.y = dm->plane.y / ((double)dm->winh / (double)dm->winw);
	dm->owinh = dm->winh;
	dm->owinw = dm->winw;
	ft_bzero(&dm->key, sizeof(t_key));
}

void	resize_window(t_doom *dm)
{
	dm->winw = dm->event.window.data1;
	dm->winh = dm->event.window.data2;
	if (dm->winw < 720 || dm->winh < 480)
	{
		SDL_SetWindowSize(dm->win, 720, 480);
		dm->winw = 720;
		dm->winh = 480;
	}
	dm->img = init_image(dm);
	if (!(dm->rend = SDL_GetRenderer(dm->win)))
		error_out(REN_ERROR, dm);
	free_vram(dm);
	alloc_vram(dm);
	wind_default(dm);
}

void	reset_position(t_doom *dm)
{
	dm->pos = dm->spw;
	dm->dir.x = 1.0;
	dm->dir.y = 0.0;
	dm->dir.z = 0.0;
	dm->plane.x = 0.0;
	dm->plane.y = 0.5 / ((double)dm->winh / (double)dm->winw);
	dm->plane.z = 0.5;
	dm->rotsp = 0.05;
	dm->movsp = 0.07;
	dm->camshift = 1.0 - (dm->dir.z * 2);
	dm->texbool = 1;
	dm->airbrn = 1;
	dm->alive = 1;
	dm->hp = 5;
	dm->magazine = 10;
}

void	doom_default(t_doom *dm)
{
	dm->flr = 0;
	reset_position(dm);
	dm->sbox = WINX / 2;
	ft_putnbrln(dm->mxflr);
	dm->prefps = 30;
	dm->buffer = BUFFER;
	set_variables(dm);
	sprite_set(dm, 4);
	dm->owinh = dm->winh;
	dm->owinw = dm->winw;
	wind_default(dm);
	dm->cycle = &main_menu;
	dm->keyck = &key_state_menu;
	dm->ismenu = 0;
	dm->trx = ((dm->winw / 100) * (dm->winh / 100)) / 2 + 1;
	dm->trx = 20;
	dm->camshift = 1.0f;
	dm->fpscap = 60;
	dm->dm = dm;
	alloc_vram(dm);
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(dm->music, 0);
	dm->volume = 64;
	Mix_VolumeMusic(64);
	dm->fpschar = ft_strdup("30");
}

void	reset_window(t_doom *dm, Uint8 arg)
{
	if (arg)
	{
		dm->winw = dm->event.window.data1;
		dm->winh = dm->event.window.data2;
		SDL_FreeSurface(dm->img.tex);
		SDL_DestroyTexture(dm->img.img);
		if (!(dm->rend = SDL_GetRenderer(dm->win)))
			error_out(REN_ERROR, dm);
		dm->img = init_image(dm);
	}
	free_vram(dm);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom_default(dm);
}
