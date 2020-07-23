/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/20 15:31:44 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	error_out(char *msg, t_doom *dm)
{
	ft_putendl(msg);
	//ft_putendl(SDL_GetError());
	SDL_SetRelativeMouseMode(SDL_FALSE);
	dm->killthread = 1;
	if (!ft_strcmp(msg, WLF_ERROR))
		exit(0);
	if (!ft_strcmp(msg, FLR_ERROR))
		dm->mxflr = dm->flr - 49;
	if (dm->gfx)
		destroy_gfx(dm, -1);
	if (dm->area)
		free_map(dm, -1, -1);
	if (dm->tex)
		SDL_DestroyTexture(dm->tex);
	if (dm->img.tex)
		SDL_FreeSurface(dm->img.tex);
	if (dm->rend)
		SDL_DestroyRenderer(dm->rend);
	if (dm->win)
		SDL_DestroyWindow(dm->win);
	if (dm->gpad)
		SDL_GameControllerClose(dm->gpad);
	SDL_WaitThread(dm->fpsthread, NULL);
	SDL_Quit();
	ft_bzero(dm, sizeof(dm));
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

void	init_audio(t_doom *dm)
{
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		ft_putendl("Failed to initialize SDL_Mixer!");
	}
	dm->music = Mix_LoadMUS("Audio/Music/scapemain.wav");
	dm->readyForAction = Mix_LoadWAV("Audio/SoundEffects/ready_for_action.wav");
	//dm->doorClose = Mix_LoadWAV("Audio/SoundEffects/doorclose.wav");
	//dm->doorOpen = Mix_LoadWAV("Audio/SoundEffects/dooropen.wav");
	dm->reload = Mix_LoadWAV("Audio/SoundEffects/reload.wav");
	dm->gunshot = Mix_LoadWAV("Audio/SoundEffects/gunshot.wav");
}

void	setup(t_doom *dm)
{
	//SDL_Thread* capper;

	dm->spawn.x = 2.51;
	dm->spawn.y = 2.51;
	dm->spawn.z = 2.5;
	init_audio(dm);
	doom_default(dm);
	if (dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)dm->pos.x] != 1)
		error_out(SPW_ERROR, dm);
	dm->fpsthread = SDL_CreateThread(fps_counter, "fps counter", (void*)dm);
	char* path = SDL_GetBasePath();
	printf("Exec path: %s\n", path);
	SDL_free(path);
	if (!(dm->joblist = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->setdone = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->lock = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->cond = SDL_CreateCond()))
		error_out(MEM_ERROR, dm);
	SDL_LockMutex(dm->lock);
	dm->done = (int*)malloc(4);
	*dm->done = 0;
	while (1)
	{
		//if (dm->isfpscap && !dm->ismenu)
		//	capper = SDL_CreateThread(fps_capper, "FPS limiter", dm);
		game_loop(dm);
		/*if (dm->limit)
		{
			SDL_WaitThread(capper, NULL);
			dm->limit = 0;
		}*/
	}
}

int		main(int ac, char **av)
{
	t_doom	*dm;

	if (!(dm = (t_doom*)malloc(sizeof(t_doom))))
		error_out(WLF_ERROR, dm);
	ft_bzero(dm, sizeof(t_doom));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_out(SDL_ERROR, dm);
	ft_putstr("Args: ");
	//ft_putnbrln(ac);
	//if (!IMG_Init(IMG_INIT_XPM))
	//	error_out(IMG_ERROR, dm);
	//if (ac != 4 && ac != 0)
	//	error_out(USAGE, dm);
	dm->tile = 2;
	if (dm->tile < 1 || dm->tile > 6)
		error_out(USAGE, dm);
	dm->mxflr = 9;
	if (dm->mxflr < 1 || dm->mxflr > 9)
		error_out(USAGE, dm);
	if (!(dm->win = SDL_CreateWindow("DoomNukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0)))
		error_out(WIN_ERROR, dm);
	//SDL_CreateWindowAndRenderer(WINX, WINY, 0, &(dm->win), &(dm->rend));
	if (!(dm->rend = SDL_CreateRenderer(dm->win, -1, SDL_RENDERER_SOFTWARE)))
		if (!(dm->rend = SDL_GetRenderer(dm->win)))
			error_out(REN_ERROR, dm);
	dm->img = init_image(dm);
	/*if (!(dm->gpad = SDL_GameControllerOpen(0)))
		ft_putendl(PAD_ERROR);
	else
		ft_putendl(SDL_GameControllerName(dm->gpad));
	if (SDL_GameControllerAddMappingsFromFile("mapping.txt") == -1)
		ft_putendl("UWU");*/
	dm->winb = 1;
	dm->winh = dm->img.tex->h;
	dm->winw = dm->img.tex->w;
	printf("Comp map\n");
	comp_map(dm);//, "Null");
	printf("Comp GFX\n");
	comp_gfx(dm, 0);
	setup(dm);
	return (0);
}
