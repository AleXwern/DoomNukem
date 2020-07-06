/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:00:00 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/06 15:40:11 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	wind_default(t_doom *wlf)
{
	double	temp;

	wlf->keyminus = 0;
	wlf->keyplus = 0;
	wlf->shift = 0;
	wlf->crouching = 0;
	wlf->keym = 0;
	wlf->keyi = 0;
	wlf->mousemovement = 0;
	wlf->fps = 0;
	wlf->plane.x = wlf->plane.x * ((double)wlf->owinh / (double)wlf->owinw);
	wlf->plane.y = wlf->plane.y * ((double)wlf->owinh / (double)wlf->owinw);
	wlf->plane.x = wlf->plane.x / ((double)wlf->winh / (double)wlf->winw);
	wlf->plane.y = wlf->plane.y / ((double)wlf->winh / (double)wlf->winw);
	wlf->owinh = wlf->winh;
	wlf->owinw = wlf->winw;
}

void	doom_default(t_doom *wlf)
{
	wlf->flr = 0;
	wlf->posx = 2.5;
	wlf->posy = 2.5;
	wlf->posz = 2.5;
	wlf->dir.x = 1.0;
	wlf->dir.y = 0.0;
	wlf->dir.z = 0.0;
	wlf->plane.x = 0.0;
	wlf->plane.y = 0.5 / ((double)wlf->winh / (double)wlf->winw);
	wlf->plane.z = 0.5;
	wlf->rotsp = 0.05;
	wlf->movsp = 0.0712;
	wlf->rng = 0.0;
	wlf->texbool = 1;
	wlf->sbox = WINX / 2;
	wlf->mxflr--;
	wlf->sel = -1;
	wlf->accesscard = 0;
	wlf->prefps = 30;
	wlf->buffer = BUFFER;
	load_animsprite(wlf);
	wlf->owinh = wlf->winh;
	wlf->owinw = wlf->winw;
	wind_default(wlf);
	wlf->cycle = &render;
	wlf->keyck = &key_state_game;
	wlf->trx = ((wlf->winw / 100) * (wlf->winh / 100)) / 2 + 1;
	wlf->trx = 20;
	wlf->camshift = 1.0f;
	wlf->fpscap = 60;
	if (!(wlf->maparr = (int*)malloc(sizeof(int) * wlf->winw * wlf->winh)))
		error_out(MEM_ERROR, wlf);
	if (!(wlf->wallarr = (double*)malloc(sizeof(double) * wlf->winw * wlf->winh)))
		error_out(MEM_ERROR, wlf);
	if (!(wlf->threads = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * wlf->trx)))
		error_out(MEM_ERROR, wlf);
	if (!(wlf->data_r = (t_doom*)malloc(sizeof(t_doom) * wlf->trx)))
		error_out(MEM_ERROR, wlf);
	printf("Threads: %d\n", wlf->trx);
}

void	reset_window(t_doom *wlf)
{
	wlf->winw = wlf->event.window.data1;
	wlf->winh = wlf->event.window.data2;
	SDL_FreeSurface(wlf->img.tex);
	SDL_DestroyTexture(wlf->img.img);
	if (!(wlf->rend = SDL_GetRenderer(wlf->win)))
		error_out(REN_ERROR, wlf);
	wlf->img = init_image(wlf);
	free(wlf->threads);
	free(wlf->data_r);
	free(wlf->maparr);
	free(wlf->wallarr);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom_default(wlf);
}