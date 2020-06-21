/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/06/17 16:49:38 by anystrom         ###   ########.fr       */
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
	wlf->mouseprevx = WINX / 2;
	wlf->mouseprevy = WINY / 2;
	wlf->fps = 0;
	wlf->cycle = &render;
	wlf->trx = ((wlf->winw / 100) + (wlf->winh / 100)) * 2;
	printf("Threads: %d\n", wlf->trx);
}

void	error_out(char *msg, t_doom *wolf)
{
	ft_putendl(msg);
	system("cd");
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
	if (wolf->surf)
		SDL_FreeSurface(wolf->surf);
	if (wolf->rend)
		SDL_DestroyRenderer(wolf->rend);
	if (wolf->win)
		SDL_DestroyWindow(wolf->win);
	SDL_Quit();
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
	int		quit;

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
		//SDL_WaitEvent(&(wlf->event));
		if (SDL_PollEvent(&(wlf->event)))
		{
			//ft_putnbrln(wlf->event.key.keysym.scancode);
			if (wlf->event.type == SDL_QUIT || wlf->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				error_out(FINE, wlf);
			if (wlf->event.window.event == SDL_WINDOWEVENT_RESIZED || wlf->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				wlf->winw = wlf->event.window.data1;
				wlf->winh = wlf->event.window.data2;
				if (wlf->surf)
					SDL_FreeSurface(wlf->surf);
				//if (wlf->rend)
				//	SDL_DestroyRenderer(wlf->rend);
				if (!(wlf->surf = SDL_GetWindowSurface(wlf->win)))
					error_out(WIN_ERROR, wlf);
				//if (!(wlf->rend = SDL_CreateRenderer(wlf->win, -1, SDL_RENDERER_SOFTWARE)))
				//	error_out(REN_ERROR, wlf);
				wolf_default(wlf);
			}
			else
			{
				if (wlf->event.type == SDL_KEYDOWN)
					key_hold(wlf->event.key.keysym.scancode, wlf);
				else if (wlf->event.type == SDL_KEYUP)
					key_release(wlf->event.key.keysym.scancode, wlf);
				move(wlf);
				wlf->cycle(wlf);
			}
		}
		else
			wlf->cycle(wlf);
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
	if (!(wolf->surf = SDL_GetWindowSurface(wolf->win)))
		error_out(WIN_ERROR, wolf);
	if (!(wolf->rend = SDL_CreateRenderer(wolf->win, -1, SDL_RENDERER_SOFTWARE)))
		error_out(REN_ERROR, wolf);
	wolf->winb = 1;
	wolf->winh = wolf->surf->h;
	wolf->winw = wolf->surf->w;
	printf("Comp map\n");
	comp_map(wolf, "Null");
	printf("Comp GFX\n");
	comp_gfx(wolf, 0);
	setup(wolf);
	return (0);
}
