/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:00:00 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/18 13:21:26 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

void	wind_default(t_doom *dm)
{
	double	temp;

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

void	free_vram(t_doom* dm)
{
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
	free(dm->claimline);
}

void	resize_window(t_doom *dm)
{
	dm->winw = dm->event.window.data1;
	dm->winh = dm->event.window.data2;
	if (dm->winw > 1500 || dm->winh > 960)
	{
		SDL_SetWindowSize(dm->win, 1500, 960);
		dm->winw = 1500;
		dm->winh = 960;
	}
	else if (dm->winw < 1080 || dm->winh < 720)
	{
		SDL_SetWindowSize(dm->win, 1080, 720);
		dm->winw = 1080;
		dm->winh = 720;
	}
	dm->img = init_image(dm);
	if (!(dm->rend = SDL_GetRenderer(dm->win)))
		error_out(REN_ERROR, dm);
	free(dm->threads);
	free(dm->data_r);
	free(dm->maparr);
	free(dm->wallarr);
	free(dm->claimline);
	if (!(dm->maparr = (int*)ft_memalloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (double*)ft_memalloc(sizeof(double) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)ft_memalloc(sizeof(SDL_Thread*) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)ft_memalloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
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
	ft_putnbrln(dm->mxflr);
	dm->prefps = 30;
	dm->buffer = BUFFER;
	set_variables(dm);
	sprite_set(dm);
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
	if (!(dm->maparr = (int*)ft_memalloc(sizeof(int) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->wallarr = (double*)ft_memalloc(sizeof(double) * dm->winw * dm->winh)))
		error_out(MEM_ERROR, dm);
	if (!(dm->threads = (SDL_Thread**)ft_memalloc(sizeof(SDL_Thread*) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(dm->data_r = (t_doom*)ft_memalloc(sizeof(t_doom) * dm->trx)))
		error_out(MEM_ERROR, dm);
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(dm->music, 0);
	dm->volume = 64;
	Mix_VolumeMusic(64);
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
