/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/13 15:22:57 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	error_out(char *msg, t_doom *wolf)
{
	ft_putendl(msg);
	//ft_putendl(SDL_GetError());
	SDL_SetRelativeMouseMode(SDL_FALSE);
	wolf->killthread = 1;
	if (!ft_strcmp(msg, WLF_ERROR))
		exit(0);
	if (!ft_strcmp(msg, FLR_ERROR))
		wolf->mxflr = wolf->flr - 49;
	if (wolf->gfx)
		destroy_gfx(wolf, -1);
	if (wolf->area)
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
	system("leaks doom-nukem");
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
	SDL_Thread* capper;

	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		ft_putendl("Failed to initialize SDL_Mixer!");
	}
	wlf->music = Mix_LoadMUS("Audio/Music/scapemain.wav");
	wlf->readyForAction = Mix_LoadWAV("Audio/SoundEffects/ready_for_action.wav");
	doom_default(wlf);
	if (wlf->area[2][(int)wlf->posy][(int)wlf->posx] != 1)
		error_out(SPW_ERROR, wlf);
	wlf->fpsthread = SDL_CreateThread(fps_counter, "fps counter", (void*)wlf);
	char* path = SDL_GetBasePath();
	printf("Exec path: %s\n", path);
	SDL_free(path);
	while (1)
	{
		//if (wlf->isfpscap && !wlf->ismenu)
		//	capper = SDL_CreateThread(fps_capper, "FPS limiter", wlf);
		game_loop(wlf);
		/*if (wlf->limit)
		{
			SDL_WaitThread(capper, NULL);
			wlf->limit = 0;
		}*/
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
	wolf->tile = 2;
	if (wolf->tile < 1 || wolf->tile > 6)
		error_out(USAGE, wolf);
	wolf->mxflr = 9;
	if (wolf->mxflr < 1 || wolf->mxflr > 9)
		error_out(USAGE, wolf);
	if (!(wolf->win = SDL_CreateWindow("DoomNukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, SDL_WINDOW_RESIZABLE)))
		error_out(WIN_ERROR, wolf);
	//SDL_CreateWindowAndRenderer(WINX, WINY, 0, &(wolf->win), &(wolf->rend));
	if (!(wolf->rend = SDL_CreateRenderer(wolf->win, -1, SDL_RENDERER_SOFTWARE)))
		if (!(wolf->rend = SDL_GetRenderer(wolf->win)))
			error_out(REN_ERROR, wolf);
	wolf->img = init_image(wolf);
	/*if (!(wolf->gpad = SDL_GameControllerOpen(0)))
		ft_putendl(PAD_ERROR);
	else
		ft_putendl(SDL_GameControllerName(wolf->gpad));
	if (SDL_GameControllerAddMappingsFromFile("mapping.txt") == -1)
		ft_putendl("UWU");*/
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
