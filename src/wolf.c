/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/25 14:23:57 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	wolf_default(t_doom *wlf)
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
	wlf->rotation = 0;
	wlf->rotsp = 0.05;
	wlf->movsp = 0.06;
	wlf->fcomb = 0;
	wlf->rng = 0.0;
	wlf->texbool = 1;
	wlf->sbox = WINX / 2;
	wlf->mxflr--;
	wlf->cur = 0;
	wlf->sel = -1;
	wlf->plr = 0;
	wlf->plrck = 0;
	wlf->keyminus = 0;
	wlf->keyplus = 0;
	wlf->shift = 0;
	wlf->crouching = 0;
	wlf->keym = 0;
	wlf->keyi = 0;
	wlf->accesscard = 0;
	wlf->fps = 0;
	wlf->mousemovement = 0;
	wlf->cycle = &render;
	wlf->trx = ((wlf->winw / 100) * (wlf->winh / 100)) / 2 + 1;
	//wlf->trx = 200;
	wlf->camshift = 1.0f;
	wlf->fpscap = 60;
	if (!(wlf->threads = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * wlf->trx)))
		error_out(MEM_ERROR, wlf);
	if (!(wlf->data_r = (t_doom*)malloc(sizeof(t_doom) * wlf->trx)))
		error_out(MEM_ERROR, wlf);
	printf("Threads: %d\n", wlf->trx);
}

void	error_out(char *msg, t_doom *wolf)
{
	ft_putendl(msg);
	ft_putendl(SDL_GetError());
	wolf->killthread = 1;
	if (!ft_strcmp(msg, WLF_ERROR))
		exit(0);
	if (!ft_strcmp(msg, FLR_ERROR))
		wolf->mxflr = wolf->flr - 49;
	if (wolf->gfx)
		destroy_gfx(wolf, -1);
	if (wolf->map)
		free_map(wolf, -1, -1);
	if (wolf->tex)
		SDL_DestroyTexture(wolf->tex);
	if (wolf->img.tex)
		SDL_FreeSurface(wolf->img.tex);
	if (wolf->rend)
		SDL_DestroyRenderer(wolf->rend);
	if (wolf->win)
		SDL_DestroyWindow(wolf->win);
	if (wolf->gpad)
		SDL_GameControllerClose(wolf->gpad);
	SDL_WaitThread(wolf->fpsthread, NULL);
	SDL_Quit();
	ft_bzero(wolf, sizeof(wolf));
	system("leaks doomdemo");
	exit(0);
}

void	free_memory(char **arr)
{
	int y;

	y = 0;
	while (arr[y])
		y++;
	while (y-- > 0)
		free(arr[y]);
	free(arr);
	arr = NULL;
}

void	setup(t_doom *wlf)
{
	int			quit;
	SDL_Thread* capper;

	wolf_default(wlf);
	if (wlf->map[2][(int)wlf->posy][(int)wlf->posx] != 1)
		error_out(SPW_ERROR, wlf);
	quit = 0;
	wlf->fpsthread = SDL_CreateThread(fps_counter, "fps counter", (void*)wlf);
	char* path = SDL_GetBasePath();
	printf("Exec path: %s\n", path);
	SDL_free(path);
	while (!quit)
	{
		capper = SDL_CreateThread(fps_capper, "FPS limiter", wlf);
		if (SDL_PollEvent(&(wlf->event)))
		{
			//SDL_PumpEvents();
			if (wlf->event.type == SDL_QUIT || wlf->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				error_out(FINE, wlf);
			if (wlf->event.window.event == SDL_WINDOWEVENT_RESIZED || wlf->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				free(wlf->threads);
				free(wlf->data_r);
				wlf->winw = wlf->event.window.data1;
				wlf->winh = wlf->event.window.data2;
				if (wlf->img.tex)
					SDL_FreeSurface(wlf->img.tex);
				if (!(wlf->rend = SDL_GetRenderer(wlf->win)))
					error_out(REN_ERROR, wlf);
				wlf->img = init_image(wlf);
				wolf_default(wlf);
			}
			if (wlf->event.key.state == SDL_PRESSED)
				key_hold(wlf->event.key.keysym.scancode, wlf);
			if (wlf->event.key.state == SDL_RELEASED)
				key_release(wlf->event.key.keysym.scancode, wlf);
			if (wlf->event.button.type == SDL_MOUSEBUTTONDOWN)//Mousebuttons: Left enables mouse-look-around. Right disables it.
			{
				if (wlf->event.button.button == SDL_BUTTON_LEFT)
				{
					wlf->mousemovement = 0;
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				if (wlf->event.button.button == SDL_BUTTON_RIGHT)
				{
					wlf->mousemovement = 1;
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}
			}
			if (wlf->mousemovement)//using mouse to look around
			{
				if (wlf->event.motion.xrel > 0)
					mouse_movex(0, wlf);
				if (wlf->event.motion.xrel < 0)
					mouse_movex(1, wlf);
				if (wlf->event.motion.yrel > 0)
					mouse_movey(0, wlf);
				if (wlf->event.motion.yrel < 0)
					mouse_movey(1, wlf);
			}
			//if (wlf->event.cbutton.state == SDL_PRESSED)
			//	key_hold(wlf->event.cbutton.button, wlf);
			//if (wlf->event.cbutton.state == SDL_RELEASED)
			//	key_release(wlf->event.cbutton.button, wlf);
			wlf->cycle(wlf);
		}
		move(wlf);
		wlf->cycle(wlf);
		SDL_WaitThread(capper, NULL);
	}
}

int		main(int ac, char **av)
{
	t_doom	*wolf;

	if (!(wolf = (t_doom*)malloc(sizeof(t_doom))))
		error_out(WLF_ERROR, wolf);
	ft_bzero(wolf, sizeof(t_doom));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_out(SDL_ERROR, wolf);
	ft_putstr("Args: ");
	ft_putnbrln(ac);
	//if (!IMG_Init(IMG_INIT_XPM))
	//	error_out(IMG_ERROR, wolf);
	//if (ac != 4 && ac != 0)
	//	error_out(USAGE, wolf);
	wolf->tile = 6;
	if (wolf->tile < 1 || wolf->tile > 6)
		error_out(USAGE, wolf);
	wolf->mxflr = 5;
	if (wolf->mxflr < 1 || wolf->mxflr > 9)
		error_out(USAGE, wolf);
	if (!(wolf->win = SDL_CreateWindow("DoomNukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, SDL_WINDOW_RESIZABLE)))
		error_out(WIN_ERROR, wolf);
	//SDL_CreateWindowAndRenderer(WINX, WINY, 0, &(wolf->win), &(wolf->rend));
	wolf->img = init_image(wolf);
	if (!(wolf->rend = SDL_CreateRenderer(wolf->win, -1, SDL_RENDERER_SOFTWARE)))
		if (!(wolf->rend = SDL_GetRenderer(wolf->win)))
			error_out(REN_ERROR, wolf);
	//if (!(wolf->gpad = SDL_GameControllerOpen(1)))
	//	ft_putendl(PAD_ERROR);
	//else
	//	ft_putendl(SDL_GameControllerName(wolf->gpad));
	wolf->winb = 1;
	wolf->winh = wolf->img.tex->h;
	wolf->winw = wolf->img.tex->w;
	printf("Comp map\n");
	comp_map(wolf, "Null");
	printf("Comp GFX\n");
	comp_gfx(wolf, 0);
	setup(wolf);
	return (0);
}
