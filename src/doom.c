/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkeinane <vkeinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/12/29 12:27:17 by vkeinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

/*
**	system("leaks doom-nukem");
*/

void	error_out(char *msg, t_doom *dm)
{
	ft_putendl(msg);
	dm->killthread = 1;
	if (dm->dev)
		ft_printmem(dm, sizeof(t_doom));
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WaitThread(dm->fpsthread, NULL);
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

void	init_audio(t_doom *dm)
{
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		ft_putendl("Failed to initialize SDL_Mixer!");
	dm->music = Mix_LoadMUS(MUSIC);
	dm->reload = Mix_LoadWAV("Audio/SoundEffects/reload.wav");
	dm->gunshot = Mix_LoadWAV("Audio/SoundEffects/gunshot.wav");
	dm->jetpacksound = Mix_LoadWAV("Audio/SoundEffects/jetpack.wav");
	dm->doorsound = Mix_LoadWAV("Audio/SoundEffects/door.wav");
	dm->teleport = Mix_LoadWAV("Audio/SoundEffects/teleport.wav");
	dm->doorknob = Mix_LoadWAV("Audio/SoundEffects/doorknob.wav");
	dm->ishit = Mix_LoadWAV("Audio/SoundEffects/gettinghit.wav");
	dm->death = Mix_LoadWAV("Audio/SoundEffects/osrsDeath.wav");
	dm->mondeath = Mix_LoadWAV("Audio/SoundEffects/osrsMonsterDeath.wav");
	dm->windowbrk = Mix_LoadWAV("Audio/SoundEffects/windowShatter.wav");
	dm->doorsliding = Mix_LoadWAV("Audio/SoundEffects/doorsliding.wav");
	dm->victory = Mix_LoadWAV("Audio/SoundEffects/victory.wav");
	dm->jump = Mix_LoadWAV("Audio/SoundEffects/jump.wav");
}

void	setup(t_doom *dm)
{
	init_audio(dm);
	doom_default(dm);
	dm->area[(int)dm->pos.z][(int)dm->pos.y][(int)dm->pos.x].b = 1;
	dm->fpsthread = SDL_CreateThread(fps_counter, "fps counter", (void*)dm);
	while (1)
		game_loop(dm);
}

int		main(int ac, char **av)
{
	t_doom	*dm;

	if (!(dm = (t_doom*)ft_memalloc(sizeof(t_doom))))
		error_out(DOOM_ERROR, dm);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_out(SDL_ERROR, dm);
	if (ac >= 2)
		dev_status(dm, av[1]);
	dm->ax = ax_init();
	dm->tile = 4;
	if (!(dm->win = SDL_CreateWindow("DoomNukem", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0)))
		error_out(WIN_ERROR, dm);
	if (!(dm->rend = SDL_CreateRenderer(dm->win, -1, SDL_RENDERER_SOFTWARE)))
		if (!(dm->rend = SDL_GetRenderer(dm->win)))
			error_out(REN_ERROR, dm);
	dm->img = init_image(dm);
	dm->spw = (t_vector){.x = 2.51, .y = 2.51, .z = 2.35};
	comp_map(dm);
	comp_gfx(dm);
	ft_putnbrln(sizeof(t_doom));
	setup(dm);
	return (0);
}
