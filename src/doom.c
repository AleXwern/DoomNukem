/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 16:17:21 by anystrom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	error_out(char *msg, t_doom *dm)
{
	ft_putendl(msg);
	//network_test(dm);
	ft_putnbrln(sizeof(double*));
	dm->killthread = 1;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WaitThread(dm->fpsthread, NULL);
	SDL_Quit();
	ft_putnbrln(sizeof(t_type));
	//system("leaks doom-nukem");
	exit(0);
	//Things below just in case.
	/*SDL_SetRelativeMouseMode(SDL_FALSE);
	dm->killthread = 1;
	if (!ft_strcmp(msg, DOOM_ERROR))
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
	//printf("%lu %ld\n", sizeof(t_block), sizeof(long));
	exit(0);*/
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
	dm->reload = Mix_LoadWAV("Audio/SoundEffects/reload.wav");
	dm->gunshot = Mix_LoadWAV("Audio/SoundEffects/gunshot.wav");
	dm->jetpack = Mix_LoadWAV("Audio/SoundEffects/jetpack.wav");
	dm->doorsound = Mix_LoadWAV("Audio/SoundEffects/door.wav");
	dm->teleport = Mix_LoadWAV("Audio/SoundEffects/teleport.wav");
	dm->doorknob = Mix_LoadWAV("Audio/SoundEffects/doorknob.wav");
	dm->gettingHit = Mix_LoadWAV("Audio/SoundEffects/gettinghit.wav");
	dm->death = Mix_LoadWAV("Audio/SoundEffects/osrsDeath.wav");
	dm->mondeath = Mix_LoadWAV("Audio/SoundEffects/osrsMonsterDeath.wav");
	dm->windowbrk = Mix_LoadWAV("Audio/SoundEffects/windowShatter.wav");
	dm->doorsliding = Mix_LoadWAV("Audio/SoundEffects/doorsliding.wav");
}

void	setup(t_doom *dm)
{
	//SDL_Thread* capper;
	init_audio(dm);
	doom_default(dm);
	printf("Spawn at %hhu\n", dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)dm->pos.x].b);
	dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)dm->pos.x].b = 1;
	dm->fpsthread = SDL_CreateThread(fps_counter, "fps counter", (void*)dm);
	char* path = SDL_GetBasePath();
	printf("Exec path: %s\n", path);
	SDL_free(path);
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
		error_out(DOOM_ERROR, dm);
	ft_bzero(dm, sizeof(t_doom));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_out(SDL_ERROR, dm);
	dm->tile = 4;
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
	dm->winb = 1;
	dm->winh = dm->img.tex->h;
	dm->winw = dm->img.tex->w;
	dm->spawn.x = 2.51;
	dm->spawn.y = 2.51;
	dm->spawn.z = 2.5;
	comp_map(dm);
	comp_gfx(dm, 0);
	setup(dm);
	return (0);
}
