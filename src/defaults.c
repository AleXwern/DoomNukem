/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:00:00 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/21 15:49:44 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	wind_default(t_doom *dm)
{
	double	temp;

	dm->shift = 0;
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
	dm->img = init_image(dm);
	//SDL_FreeSurface(dm->img.tex);
	//SDL_DestroyTexture(dm->img.img);
	if (!(dm->rend = SDL_GetRenderer(dm->win)))
		error_out(REN_ERROR, dm);
	//dm->img = init_image(dm);
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
	free(dm->claimline);
	if (!(dm->maparr = (int*)malloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (double*)malloc(sizeof(double) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)malloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->claimline = (int*)malloc(sizeof(int) * dm->winw)))
		error_out(MEM_ERROR, dm);
	ft_bzero(dm->claimline, 4 * dm->winw);
	wind_default(dm);
}

void	reset_position(t_doom *dm)
{
	dm->pos = dm->spawn;
	dm->dir.x = 1.0;
	dm->dir.y = 0.0;
	dm->dir.z = 0.0;
	dm->plane.x = 0.0;
	dm->plane.y = 0.5 / ((double)dm->winh / (double)dm->winw);
	dm->plane.z = 0.5;
	dm->rotsp = 0.05;
	dm->movsp = 0.0712;
	dm->camshift = 1.0 - (dm->dir.z * 2);
	dm->texbool = 1;
	dm->airbrn = 1;
}

void	doom_default(t_doom *dm)
{
	dm->flr = 0;
	reset_position(dm);
	dm->sbox = WINX / 2;
	//dm->mxflr--;
	ft_putnbrln(dm->mxflr);
	dm->prefps = 30;
	dm->buffer = BUFFER;
	load_animsprite(dm);
	load_gun(dm);
	load_numbers(dm);
	load_inventory(dm);
	load_keycard(dm);
	load_hp(dm);
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
	if (!(dm->maparr = (int*)malloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (double*)malloc(sizeof(double) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)malloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->claimline = (int*)malloc(sizeof(int) * dm->winw)))
		error_out(MEM_ERROR, dm);
	ft_bzero(dm->claimline, 4 * dm->winw);
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(dm->osrsMusic, 0);
	printf("Threads: %d\n", dm->trx);
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
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom_default(dm);
}
