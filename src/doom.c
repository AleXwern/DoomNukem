/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/09/25 15:05:05 by tbergkul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include "../includes/value.h"

#include <stdio.h>

void	network_test(t_doom *dm)
{
	int		done = 0;
	char	*argv;

	if (0)
		argv = "server";
	else
		argv = "client";
	if (strcmp(argv, "server") == 0)
	{
		printf("Starting server...\n");
		TCPsocket server, client;
		IPaddress ip;
		if (SDLNet_ResolveHost(&ip, NULL, 9999) == -1)
		{
			printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
			exit(1);
		}
		server = SDLNet_TCP_Open(&ip);
		if (!server)
		{
			printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
			exit(2);
		}
		while (!done)
		{
			/* try to accept a connection */
			client = SDLNet_TCP_Accept(server);
			if (!client)
			{ /* no connection accepted */
				/*printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
				SDL_Delay(100); /*sleep 1/10th of a second */
				continue;
			}

			/* get the clients IP and port number */
			IPaddress *remoteip;
			remoteip = SDLNet_TCP_GetPeerAddress(client);
			if (!remoteip)
			{
				printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
				continue;
			}

			/* print out the clients IP and port number */
			Uint32 ipaddr;
			ipaddr = SDL_SwapBE32(remoteip->host);
			printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
					(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
					remoteip->port);

			while (1)
			{
				/* read the buffer from client */
				char message[1024];
				int len = SDLNet_TCP_Recv(client, message, 1024);
				if (!len)
				{
					printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
					break;
				}
				/* print out the message */
				printf("Received: %.*s\n", len, message);
				if (message[0] == 'q')
				{
					printf("Disconecting on a q\n");
					break;
				}
				if (message[0] == 'Q')
				{
					printf("Closing server on a Q.\n");
					done = 1;
					break;
				}
			}
			SDLNet_TCP_Close(client);
		}
	}
	else if (strcmp(argv, "client") == 0)
	{
		printf("Starting client...\n");
		IPaddress ip;
		TCPsocket tcpsock;

		if (SDLNet_ResolveHost(&ip, "10.13.1.1", 9999) == -1)
		{
			printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
			exit(1);
		}

		tcpsock = SDLNet_TCP_Open(&ip);
		if (!tcpsock)
		{
			printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
			exit(2);
		}

		while (1)
		{
			printf("message: ");
			char message[1024];
			fgets(message, 1024, stdin);
			int len = strlen(message);

			/* strip the newline */
			message[len - 1] = '\0';

			if (len)
			{
				int result;

				/* print out the message */
				printf("Sending: %.*s\n", len, message);

				result =
					SDLNet_TCP_Send(tcpsock, message, len); /* add 1 for the NULL */
				if (result < len)
				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			}

			if (len == 2 && tolower(message[0]) == 'q') {
				break;
			}
		}

		SDLNet_TCP_Close(tcpsock);
	} else
	{
		printf("Choose server or client\n");
	}
	SDLNet_Quit();
	SDL_Quit();
}

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
	if (!(dm->joblist = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->setdone = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->lock = SDL_CreateMutex()))
		error_out(MEM_ERROR, dm);
	if (!(dm->cond = SDL_CreateCond()))
		error_out(MEM_ERROR, dm);
	SDL_LockMutex(dm->lock);
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
